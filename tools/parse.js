const { writeFile, readFile } = require('fs/promises');
const { join } = require('path');

/**
 * 1. dumpbin.exe /EXPORTS C:\Windows\system32\wsock32.dll /OUT:dumpbin.txt
 * 2. node parse.js dumpbin.txt wsock32
 */

(async () =>
{
	const args = process.argv.slice(2);

	if (args[0] === undefined) throw new Error('No input file');
	if (args[1] === undefined) throw new Error('No dll name');

	const content = await readFile(args[0], 'utf8');
	const lines = content.replace('\r', '').split('\n');

	let outputCpp = `#pragma once\n\n#define DLL_NAME "${args[1]}.dll"\n#define ALLFUNC(FUNC) \\\n`;
	let outputDef = `LIBRARY "${args[1].toUpperCase()}"\nEXPORTS\n\n`;
	let totalExports = 0;

	lines.forEach((line) =>
	{
		// TODO: add support for NONAME (e.g: xinput1_3.dll)
		const m = /^ *(\d+) +([0-9A-F]+)(?: +[0-9A-F]* )?(\S+)/gm.exec(line);
		if (m !== null)
		{
			console.log(line);
			totalExports++;
			outputCpp += `\tFUNC(0x${m[2].padStart(2, 0)}, ${m[3]}, ${m[1]}) \\\n`;
			outputDef += `${m[3]} = _${m[3]} @${m[1]}\n`;
		}
	});

	outputCpp += `\n#define ALLFUNC_COUNT 0x${totalExports.toString(16).toUpperCase()}\n`;

	await Promise.all([
		writeFile(join(__dirname, 'definitions.h'), outputCpp, 'utf-8'),
		writeFile(join(__dirname, 'proxy.def'), outputDef, 'utf-8'),
	]);

	console.log('Done!');
})();
