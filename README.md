# ERPLAG: a minimalist compiler
ERPLAG is a strongly typed, compiled language. It is minimalist because it currently does not encompass the full capabilities of most modern programming languages like character and string handling or defining structs/classes.

## Prerequisites
 * gcc >= 7.0
 * nasm >= 2.14.02

## How to build
1. Clone the repository  
	 `$: git clone https://github.com/MayankJasoria/Compiler-Project.git`
2. Build  
		`$: cd Compiler-Project`  
		`$: make` 

	 This should create a binary file named 'compiler' in the same directory.	
3. Execute  
	 Run the ERPLAG compiler in the following manner:minimalist because it currently does not encompass the full capabilities of most modern programming languages like character and string handling or defining structs/classes.

## Prerequisites
 * gcc >= 7.0
 * nasm >= 2.14.02

## How to build
1. Clone the repository  
	 `$: git clone https://github.com/MayankJasoria/Compiler-Project.git`
2. Build  
		`$: cd Compiler-Project`  
		`$: make` 

	 This should create a binary file named 'compiler' in the same directory.	
3. Execute  
	 Run the ERPLAG compiler in the following manner:
		`$: ./compiler <source-code> <assembly-output-file>`		 

## Language Features
ERPLAG supports the following features:
* **Primitive datatypes** - integers, floating points
* **Non-primitive** - arrays, boolean
* **Basic arithmetic operations** - add, subtract, multiply, divide
* **Statements**:
	- ___Comments___  
		Examples:
		```
		** single line comment **

		**
		Multiline comment
		**
		```
	- ___Declarative___  
		Examples:  
		Declaring variables:
		```
		declare index:integer;
		declare t:boolean;
		declare s:real;
		```
		Declaring a module:
		```
		declare module readArr;
		```
	- ___Assignment___  
		Examples:
		```
		sum := sum + 4; ** Integer assignment **
		pi := 3.14; ** Floating point assignment **
		bool2 := a < b ** Boolean assignment **
		arr2 := arr1; ** Assigning one array into another variable **
		```
	- ___Input/output___  
		Examples:  
		Input:
		```
		get_value(var);
		``` 

		Output
		```
		print(var);
		```
	- ___Conditional___  
		Examples:
		```
		switch(c) ** switch case on boolean **
		start
			case true:
				** statements **;
				break;
			case false: 
				** statements **;
				break;
		end

		switch(int1) ** switch case on integer **
		start
			case 1:
				** statements **
				break;
			case 2:
				** statements **
			case 3:
				** statements **
				break;
			default:
				** statements **
		end
		```
	- ___Iterative___  
		Examples:
		While loop
		```
		while(a >= b)
		start
			** statements **
		end
		```
		For loop
		```
		for(idx1 in 1..10)
		start
			** statements **
		end
		```
	- ___Module declaration and call___  
		Examples:

		Driver (main) module   
		_Note_: Driver module is the entry-point of an ERPLAG program.
		```
		<<<driver program>>>
		start
			** statements **
		end
		```

		Module declaration
		```
		declare module m1; ** allows module definition to be given after 'driver' **

		<<module arraySum>> ** Declaration and definition may be combined this way, if it appears in the code before driver module **
		takes input[list:array[1..15] of real, n:integer];
		returns  [sum:real]; 
		start
			** statements **
		end
		
		<<module printReal>>
		takes input[n:real];
		start
			print(n);
		end
		```
		
		Module call
		```
		[sum]:= use module arraySum with parameters A,k;
		use module printReal with parameters pi;
		```

A detailed language specification can be found [here](/Grammar%20and%20Specs/Language%20specifications.pdf)

* **Non-primitive** - arrays, boolean
* **Basic arithmetic operations** - add, subtract, multiply, divide
* **Statements**:
	- ___Comments___  
		Examples:
		```
		** single line comment **

		**
		Multiline comment
		**
		```
	- ___Declarative___  
		Examples:  
		Declaring variables:
		```
		declare index:integer;
		declare t:boolean;
		declare s:real;
		```
		Declaring a module:
		```
		declare module readArr;
		```
	- ___Assignment___  
		Examples:
		```
		sum := sum + 4; ** Integer assignment **
		pi := 3.14; ** Floating point assignment **
		bool2 := a < b ** Boolean assignment **
		arr2 := arr1; ** Assigning one array into another variable **
		```
	- ___Input/output___  
		Examples:  
		Input:
		```
		get_value(var);
		``` 

		Output
		```
		print(var);
		```
	- ___Conditional___  
		Examples:
		```
		switch(c) ** switch case on boolean **
		start
			case true:
				** statements **;
				break;
			case false: 
				** statements **;
				break;
		end

		switch(int1) ** switch case on integer **
		start
			case 1:
				** statements **
				break;
			case 2:
				** statements **
			case 3:
				** statements **
				break;
			default:
				** statements **
		end
		```
	- ___Iterative___  
		Examples:
		While loop
		```
		while(a >= b)
		start
			** statements **
		end
		```
		For loop
		```
		for(idx1 in 1..10)
		start
			** statements **
		end
		```
	- ___Module declaration and call___  
		Examples:

		Driver (main) module   
		_Note_: Driver module is the entry-point of an ERPLAG program.
		```
		<<<driver program>>>
		start
			** statements **
		end
		```

		Module declaration
		```
		declare module m1; ** allows module definition to be given after 'driver' **

		<<module arraySum>> ** Declaration and definition may be combined this way, if it appears in the code before driver module **
		takes input[list:array[1..15] of real, n:integer];
		returns  [sum:real]; 
		start
			** statements **
		end
		
		<<module printReal>>
		takes input[n:real];
		start
			print(n);
		end
		```
		
		Module call
		```
		[sum]:= use module arraySum with parameters A,k;
		use module printReal with parameters pi;
		```

A detailed language specification can be found [here](/Grammar%20and%20Specs/Language%20specifications.pdf)
