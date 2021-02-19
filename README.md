# CharCode
Yes, it is like Brainfuck


A quick lil' howto:

Put your code in "code.txt"
The file must start with how many integers are in the array, followed with a /
Following, the initial values of each index can be assigned by writing the numbers, each followed by a /
If an index is not initialised, it will start with a default of 0
After the array has been initialised, the operands must follow
Operations are executed left to right, and any arguments must follow immediately after the operand

"+"	add to the current index, or increment if no argument is present
	arguments: the index to add to the current index

"-"	subtract from the current index, or decrement if no argument is present
	arguments: the index to subtract from the current index

"<"	jump to the index to the left

">"	jump to the index to the right

"|"	jump to an index
	arguments: the index to jump to

"="	input into current index

"?"	output from current index



Notes:
Operands and arguments do not require a terminating character; the beginning of another operation is sufficient to terminate the previous one
Spaces are not permitted at all
Only the first line of the document is read. Anything after the first line will be ignored by the interpreter
By default, the program looks at "code.txt". This can be changed by passing the desired path as a command line argument
	
