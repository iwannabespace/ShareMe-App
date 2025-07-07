sfml_include = /opt/homebrew/Cellar/sfml/3.0.0/include
cpr_include = /opt/homebrew/Cellar/cpr/1.11.1/include
nlohmann_include = /opt/homebrew/Cellar/nlohmann-json/3.11.3/include
openssl_include = /opt/homebrew/Cellar/openssl@3/3.4.0/include
asio_include = /opt/homebrew/Cellar/asio/1.30.2/include
sfml_lib = /opt/homebrew/Cellar/sfml/3.0.0/lib
cpr_lib = /opt/homebrew/Cellar/cpr/1.11.1/lib
openssl_lib = /opt/homebrew/Cellar/openssl@3/3.4.0/lib

files = main.cpp src/*.cpp src/**/*.cpp src/**/**/*.cpp external/**/*.cpp
includes = -I${sfml_include} -I${cpr_include} -I${nlohmann_include} -I${openssl_include} -I${asio_include}
libs = -L${sfml_lib} -L${cpr_lib} -L${openssl_lib}
cpp_version = -std=c++20
flags = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lcpr -lssl -lcrypto
output = -o ShareMe

run: compile
	./ShareMe

compile:
	g++ ${files} ${includes} ${libs} ${cpp_version} ${flags} ${output}

clean: ShareMe
	rm ShareMe