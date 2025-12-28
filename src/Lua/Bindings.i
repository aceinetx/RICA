%module rica
%include "std_string.i"
%include "std_vector.i"

%{
class Engine {
public:
	static Engine& getInstance();
};
%}

class Engine {
public:
	static Engine& getInstance();
};
