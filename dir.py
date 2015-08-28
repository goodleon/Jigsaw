
import os

for p, ds, fs in os.walk('Classes'):
	for f in fs:
		if f.endswith('cpp') or f.endswith('c'):
			cmd = '$(LOCAL_PATH)/../../../'+os.path.join(p,f)+' \\'
			print cmd
