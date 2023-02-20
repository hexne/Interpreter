#include "../Debug.h"
#include "File.h"
#include <QFileDialog>
#include <fstream>

auto File::GetPath() -> Path{
	return _path;
}

std::string_view File::GetContent() {
	return _content;
}
File::File(QWidget* window) :_window(window) {  }

auto File::Create() -> Path {
	_path = QFileDialog::getSaveFileName(_window,
		"创建文件",
		".", 
		"C语言文件(*.c);;All Files (*)").toStdString();
	
	std::fstream file_system(_path,std::ios::in | std::ios::out | std::ios::trunc);
	return _path;
}

void File::Open() {
	_path = QFileDialog::getOpenFileName(
		_window,
		"打开文件",
		"/",
		"C 文件(*.c);;\
		文本文件(*.txt);;\
		所有文件(*.*)").toStdString();
	Read();

}

void File::Read() {
	_content.clear();
	if (_path.empty()) {
		return;
	}
	std::fstream file_stream(_path);
	std::string line;
	while (std::getline(file_stream, line)) {
		_content += line + "\n";
	}
}
void File::Read(Path file_path) {
	_path = file_path;
	Read();
}

void File::Save(std::string_view updata_text) {
	if (_path.empty()) {
		_path = Create();
	}
	std::fstream file_system(_path);
	
	file_system << updata_text;

}

void File::Close() {
	_path.clear();
	_content.clear();
}

