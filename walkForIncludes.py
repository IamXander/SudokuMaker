#hpp, h, hh

import os

includes = [];

for root, dirs, files in os.walk('.'):
	print(root);
	print(dirs);
	print(files);
	if root.endswith('/include'):
		includes.append(root);
	# print(root, "consumes", end=" ")
	# print(sum(getsize(join(root, name)) for name in files), end=" ")
	# print("bytes in", len(files), "non-directory files")
	# if 'CVS' in dirs:
	#     dirs.remove('CVS')  # don't visit CVS directories
f = open('.clang_complete', 'w')
for include in includes:
	f.write('-I' + include + '\n')
f.close()
print(includes)
