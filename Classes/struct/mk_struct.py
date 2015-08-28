import sys
import json
import os

def header_handler(item):
	ret = \
'''
public:
	void set_name(ctype val);
	ctype name();
	ctype name() const;
private:
	ctype m_name;
'''
	ret = ret.replace('name', item["name"])
	ret = ret.replace('ctype', item["ctype"])
	return ret

def cpp_handler(class_name, item):
	ret = \
'''
void class_name::set_name(ctype val)
{
	m_name = val;
}
ctype class_name::name()
{
	return m_name;
}
ctype class_name::name() const
{
	return m_name;
}
'''
	ret = ret.replace('class_name', class_name)
	ret = ret.replace('name', item["name"])
	ret = ret.replace('ctype', item["ctype"])
	return ret

def cpp_attr_init( attrs ):
	ret = ''
	for item in attrs:
		if item['ctype']=='bool': ret = ret + '\n\tm_%s = false;'%(item['name'])
		elif item['ctype']=='int': ret = ret + '\n\tm_%s = 0;'%(item['name'])
	return ret

def mk_header(class_name, attrs):
	temp = open('header-temp.txt').read().replace('class_name', class_name)
	fos = open(class_name+'.pb.h', 'w')
	header_attrs = ''
	for item in attrs:
		header_attrs = header_attrs + header_handler(item)

	temp = temp.replace('attrs', header_attrs)
	fos.write(temp)
	fos.close()

def mk_cpp(class_name, attrs):
	temp = open('cpp-temp.txt').read().replace('class_name', class_name)
	fos = open(class_name+'.pb.cpp', 'w')
	cpp_function = ''
	for item in attrs:
		cpp_function = cpp_function + cpp_handler(class_name, item)

	temp = temp.replace('attrs_init', cpp_attr_init(attrs))
	temp = temp.replace('cpp_function', cpp_function)
	fos.write(temp)
	fos.close()


def parse_one_file(src_file):
	attrs = json.load( open(src_file) )

	class_name = os.path.splitext(src_file)[0]

	mk_header(class_name, attrs)
	mk_cpp(class_name, attrs)

def parse_cur_dir():
	for f in os.listdir('.'):
		if f.endswith('.json'):
			parse_one_file(f)
			print '%s'%f
if __name__ == '__main__':
	parse_cur_dir()
	# argc = len(sys.argv)
	# if argc<=1:
	# 	print 'args error:', sys.argv
	# else:
	# 	main(sys.argv[1])






