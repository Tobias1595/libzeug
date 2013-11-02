
#include <fstream>

#include <iozeug/readfile.h>


namespace zeug 
{

bool readFile(const std::string & filePath, std::string & content)
{
	// http://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html

	std::ifstream in(filePath, std::ios::in | std::ios::binary);

	if (!in)
		return false;

	content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
	return true;
}

// convenience
std::string readFile(const std::string & filePath)
{
	std::string content;
	readFile(filePath, content);

	return content;
}

} // namespace zeug
