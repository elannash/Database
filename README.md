# SQLite Clone From Scratch
## Project Overview

This project implements lower-level data structures and libraries, as well as high-level classes, to create a relational database management system. At its highest level, it consists of three main classes:

* SQL
     - Takes SQL-esque user commands and manages a database of tables written into storage.
     - Interacts with the Parser class to determine the type of command being executed by the user.
     - Interacts with the Table class to perform select commands.
     - Has the capability to process a batch file in .txt format and execute the commands contained within it.

* Parser
     - Tokenizes string input from the user and creates a parse tree based on the query.
     - Utilizes a graph in the form of an adjacency matrix to verify queries.

* Table
     - Manages a single table, but has functions to open other tables and select data values adhering to certain conditions.
     - Utilizes B+ Trees to index data.
     - Stores data in binary files.
     - Uses the Shunting Yard algorithm to convert infix conditions to postfix and evaluate.

### Known Issues:
- Missing closing quotes: The system currently lacks updated exception handling for missing closing quotes.

### TODO:
- Add support for assorted types (e.g. integer types, double types, etc)
- Implement additional SQL commands: DROP, ALTER, UPDATE commands, and more.
- Allow values to be omitted (e.g. ``insert into Table values ,, value3`` would result in the omitted values being ``NOVALUE``).
- Add support for determining current file path dynamically at runtime (currently executable must be run from project's root folder or file path issues will occur).

## Building
This project builds nearly all data structures from scratch and does not depend on any external libraries. It can be compiled on most compilers that support the C++11 standard. Alternatively, a .zip file containing all source files and the executable is available under **releases**.

### Using ``Make``
- Run ``make`` using the provided Makefile in the project's root folder
- From the project's **root directory**, run the executable: ``./build/bin/main``

### Using ``CMake``
- Run the following commands from the project's root folder in terminal:
     - ``--cmake -S . -B build``
     - ``--cmake build build``
- From the project's **root directory**, run the executable: ``./build/bin/main``

## Syntax Guide
### Table Creation
To create the "Student Table" with specific fields, use the following command: ``create table <tablename> fields <field1>, <field2>, ...``\
Example: ``create table "Student Table" fields "First Name", "Last Name", Age, Major``

### Data Insertion
To insert data into a table, use the following commands. (Note: if a trailing value is not provided, ``NOVALUE`` will be inserted in its place): ``insert into <tablename> values <value1>, <value2>, ...``\
Example: ``insert into "Student Table" values Devon, Vega, 23, "Biology"``

### Data Selection
Retrieve all rows from the table: ``select * from <tablename>``\
Example: ``select * from Employees``

Select rows where the <field> column is equal to a specific value: ``select * from <tablename> where <field> = <value>``\
Example: ``select * from "Student Table" where "First Name" = Aidan``

Select rows using <, >, <=, >= operators. **(Note comparisons are currently lexicographical)**: ``select * from <tablename> where <field> <, >, <=, >= <value>``\
Example: ``select * from Employees where Name < Michael``

Select specific fields: ``select <field1>, <field2>, ... from <tablename>``\
Example: ``select "First Name", Major from Students"``

### Advanced Queries
Select data using **and**: ``select <fields> from <tablename> where <field1> = <condition1> and <condition2>``\
Example: ``select * from Employees where "First Name" = Adam and "Last Name" = Baker``

Select data using **or**: ``select <fields> from <tablename> where <condition1> or <condition2>``\
Example: ``select * from Employees where "First Name" = Adam or Age = 34``

Use **parentheses** to group conditions: ``select <fields> from <tablename> where (<condition1> or <condition2>) and ((<condition3> or <condition4>) or <condition5>)``\
Example: ``select * from Employees where (Age = 20 or Age = 25) and (("First Name" = John or "Last Name" = Jones) or Age = 21)``

# Sample [Test](https://github.com/elannash/rdbms/blob/86123f15d15c4dcc6b39ab8de3ee614019469dc4/_tests/_test_files/test_db.cpp) Output:

<pre>
----------running test_db.cpp---------


[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from TEST_SQL
[ RUN      ] TEST_SQL.TestSql
The command:  create table "Student Table" fields "First Name", "Last Name", Age, Major
Table name: Student Table, records: 0
                   record               First Name                Last Name                      Age                    Major


The command:  insert into "Student Table" values Devon, Vega, 23, "Biology" 
Table name: Student Table, records: 1
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology

The command:  insert into "Student Table" values Ezekiel, Hensley, 24, "Economics" 
Table name: Student Table, records: 2
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics

The command:  insert into "Student Table" values Alaina, Vaughn, 18 
Table name: Student Table, records: 3
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE

The command:  insert into "Student Table" values Vance, Ward, 29, "Geography" 
Table name: Student Table, records: 4
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography

The command:  insert into "Student Table" values Avery, Adkins, 20, "Sociology" 
Table name: Student Table, records: 5
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology

The command:  insert into "Student Table" values Ariel, Acosta, 28, "Divinity" 
Table name: Student Table, records: 6
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity

The command:  insert into "Student Table" values Gregory, Sutton, 25, "Philosophy" 
Table name: Student Table, records: 7
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy

The command:  insert into "Student Table" values Miah, Mendoza, 26, "Economics" 
Table name: Student Table, records: 8
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics

The command:  insert into "Student Table" values Aidan, Jacobson, 21, "Sociology" 
Table name: Student Table, records: 9
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology

The command:  insert into "Student Table" values Hailey, Nielsen, 22, "Law" 
Table name: Student Table, records: 10
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law

The command:  insert into "Student Table" values Avery, Bryan, 21, "Geography" 
Table name: Student Table, records: 11
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography

The command:  insert into "Student Table" values Vance, Benjamin, 27, "Biology" 
Table name: Student Table, records: 12
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology

The command:  insert into "Student Table" values Lucia, Franco, 17, "Business" 
Table name: Student Table, records: 13
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business

The command:  insert into "Student Table" values Dania, Hobbs, 18 
Table name: Student Table, records: 14
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE

The command:  insert into "Student Table" values Wilson, Nichols, 22, "Economics" 
Table name: Student Table, records: 15
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics

The command:  insert into "Student Table" values Johnathan, Wilcox, 20, "Computer Sciences" 
Table name: Student Table, records: 16
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics
                       15                Johnathan                   Wilcox                       20        Computer Sciences

The command:  insert into "Student Table" values Wilson, Knight, 21, "Computer Sciences" 
Table name: Student Table, records: 17
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics
                       15                Johnathan                   Wilcox                       20        Computer Sciences
                       16                   Wilson                   Knight                       21        Computer Sciences

The command:  insert into "Student Table" values Faith, Griffith, 19, "Electrical Engineering" 
Table name: Student Table, records: 18
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics
                       15                Johnathan                   Wilcox                       20        Computer Sciences
                       16                   Wilson                   Knight                       21        Computer Sciences
                       17                    Faith                 Griffith                       19   Electrical Engineering

The command:  insert into "Student Table" values Riley, Larson, 20, "Agriculture" 
Table name: Student Table, records: 19
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics
                       15                Johnathan                   Wilcox                       20        Computer Sciences
                       16                   Wilson                   Knight                       21        Computer Sciences
                       17                    Faith                 Griffith                       19   Electrical Engineering
                       18                    Riley                   Larson                       20              Agriculture
                       
The command:  insert into "Student Table" values Aidan, Weber, 19, "Philosophy" 
Table name: Student Table, records: 20
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics
                       15                Johnathan                   Wilcox                       20        Computer Sciences
                       16                   Wilson                   Knight                       21        Computer Sciences
                       17                    Faith                 Griffith                       19   Electrical Engineering
                       18                    Riley                   Larson                       20              Agriculture
                       19                    Aidan                    Weber                       19               Philosophy

The command:  select * from "Student Table" 
Table name: _select_Student Table1, records: 20
                   record               First Name                Last Name                      Age                    Major

                        0                    Devon                     Vega                       23                  Biology
                        1                  Ezekiel                  Hensley                       24                Economics
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Vance                     Ward                       29                Geography
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Ariel                   Acosta                       28                 Divinity
                        6                  Gregory                   Sutton                       25               Philosophy
                        7                     Miah                  Mendoza                       26                Economics
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Hailey                  Nielsen                       22                      Law
                       10                    Avery                    Bryan                       21                Geography
                       11                    Vance                 Benjamin                       27                  Biology
                       12                    Lucia                   Franco                       17                 Business
                       13                    Dania                    Hobbs                       18                  NOVALUE
                       14                   Wilson                  Nichols                       22                Economics
                       15                Johnathan                   Wilcox                       20        Computer Sciences
                       16                   Wilson                   Knight                       21        Computer Sciences
                       17                    Faith                 Griffith                       19   Electrical Engineering
                       18                    Riley                   Larson                       20              Agriculture
                       19                    Aidan                    Weber                       19               Philosophy
Records selected: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 

The command:  select * from "Student Table" where "First Name" = Aidan 
Table name: _select_Student Table2, records: 2
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                 Jacobson                       21                Sociology
                        1                    Aidan                    Weber                       19               Philosophy
Records selected: 8 19 

The command:  select * from "Student Table" where "First Name" < Miah 
Table name: _select_Student Table3, records: 14
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                 Jacobson                       21                Sociology
                        1                    Aidan                    Weber                       19               Philosophy
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Ariel                   Acosta                       28                 Divinity
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Avery                    Bryan                       21                Geography
                        6                    Dania                    Hobbs                       18                  NOVALUE
                        7                    Devon                     Vega                       23                  Biology
                        8                  Ezekiel                  Hensley                       24                Economics
                        9                    Faith                 Griffith                       19   Electrical Engineering
                       10                  Gregory                   Sutton                       25               Philosophy
                       11                   Hailey                  Nielsen                       22                      Law
                       12                Johnathan                   Wilcox                       20        Computer Sciences
                       13                    Lucia                   Franco                       17                 Business
Records selected: 8 19 2 5 4 10 13 0 1 17 6 9 15 12 

The command:  select * from "Student Table" where "First Name" > Miah 
Table name: _select_Student Table4, records: 5
                   record               First Name                Last Name                      Age                    Major

                        0                    Riley                   Larson                       20              Agriculture
                        1                    Vance                     Ward                       29                Geography
                        2                    Vance                 Benjamin                       27                  Biology
                        3                   Wilson                  Nichols                       22                Economics
                        4                   Wilson                   Knight                       21        Computer Sciences
Records selected: 18 3 11 14 16 

The command:  select * from "Student Table" where "First Name" <= Miah 
Table name: _select_Student Table5, records: 15
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                 Jacobson                       21                Sociology
                        1                    Aidan                    Weber                       19               Philosophy
                        2                   Alaina                   Vaughn                       18                  NOVALUE
                        3                    Ariel                   Acosta                       28                 Divinity
                        4                    Avery                   Adkins                       20                Sociology
                        5                    Avery                    Bryan                       21                Geography
                        6                    Dania                    Hobbs                       18                  NOVALUE
                        7                    Devon                     Vega                       23                  Biology
                        8                  Ezekiel                  Hensley                       24                Economics
                        9                    Faith                 Griffith                       19   Electrical Engineering
                       10                  Gregory                   Sutton                       25               Philosophy
                       11                   Hailey                  Nielsen                       22                      Law
                       12                Johnathan                   Wilcox                       20        Computer Sciences
                       13                    Lucia                   Franco                       17                 Business
                       14                     Miah                  Mendoza                       26                Economics
Records selected: 8 19 2 5 4 10 13 0 1 17 6 9 15 12 7 

The command:  select * from "Student Table" where "First Name" >= Miah 
Table name: _select_Student Table6, records: 6
                   record               First Name                Last Name                      Age                    Major

                        0                     Miah                  Mendoza                       26                Economics
                        1                    Riley                   Larson                       20              Agriculture
                        2                    Vance                     Ward                       29                Geography
                        3                    Vance                 Benjamin                       27                  Biology
                        4                   Wilson                  Nichols                       22                Economics
                        5                   Wilson                   Knight                       21        Computer Sciences
Records selected: 7 18 3 11 14 16 

The command:  select * from "Student Table" where "Last Name" < Mendoza 
Table name: _select_Student Table7, records: 11
                   record               First Name                Last Name                      Age                    Major

                        0                    Ariel                   Acosta                       28                 Divinity
                        1                    Avery                   Adkins                       20                Sociology
                        2                    Vance                 Benjamin                       27                  Biology
                        3                    Avery                    Bryan                       21                Geography
                        4                    Lucia                   Franco                       17                 Business
                        5                    Faith                 Griffith                       19   Electrical Engineering
                        6                  Ezekiel                  Hensley                       24                Economics
                        7                    Dania                    Hobbs                       18                  NOVALUE
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Wilson                   Knight                       21        Computer Sciences
                       10                    Riley                   Larson                       20              Agriculture
Records selected: 5 4 11 10 12 17 1 13 8 16 18 

The command:  select * from "Student Table" where "Last Name" > Mendoza 
Table name: _select_Student Table8, records: 8
                   record               First Name                Last Name                      Age                    Major

                        0                   Wilson                  Nichols                       22                Economics
                        1                   Hailey                  Nielsen                       22                      Law
                        2                  Gregory                   Sutton                       25               Philosophy
                        3                   Alaina                   Vaughn                       18                  NOVALUE
                        4                    Devon                     Vega                       23                  Biology
                        5                    Vance                     Ward                       29                Geography
                        6                    Aidan                    Weber                       19               Philosophy
                        7                Johnathan                   Wilcox                       20        Computer Sciences
Records selected: 14 9 6 2 0 3 19 15 

The command:  select * from "Student Table" where "Last Name" <= Mendoza 
Table name: _select_Student Table9, records: 12
                   record               First Name                Last Name                      Age                    Major

                        0                    Ariel                   Acosta                       28                 Divinity
                        1                    Avery                   Adkins                       20                Sociology
                        2                    Vance                 Benjamin                       27                  Biology
                        3                    Avery                    Bryan                       21                Geography
                        4                    Lucia                   Franco                       17                 Business
                        5                    Faith                 Griffith                       19   Electrical Engineering
                        6                  Ezekiel                  Hensley                       24                Economics
                        7                    Dania                    Hobbs                       18                  NOVALUE
                        8                    Aidan                 Jacobson                       21                Sociology
                        9                   Wilson                   Knight                       21        Computer Sciences
                       10                    Riley                   Larson                       20              Agriculture
                       11                     Miah                  Mendoza                       26                Economics
Records selected: 5 4 11 10 12 17 1 13 8 16 18 7 

The command:  select * from "Student Table" where "Last Name" >= Mendoza 
Table name: _select_Student Table10, records: 9
                   record               First Name                Last Name                      Age                    Major

                        0                     Miah                  Mendoza                       26                Economics
                        1                   Wilson                  Nichols                       22                Economics
                        2                   Hailey                  Nielsen                       22                      Law
                        3                  Gregory                   Sutton                       25               Philosophy
                        4                   Alaina                   Vaughn                       18                  NOVALUE
                        5                    Devon                     Vega                       23                  Biology
                        6                    Vance                     Ward                       29                Geography
                        7                    Aidan                    Weber                       19               Philosophy
                        8                Johnathan                   Wilcox                       20        Computer Sciences
Records selected: 7 14 9 6 2 0 3 19 15 

The command:  select "First Name", Age, Major from "Student Table" where Age < 18 
Table name: _select_Student Table11, records: 1
                   record               First Name                      Age                    Major

                        0                    Lucia                       17                 Business
Records selected: 12 

The command:  select "First Name", Age, Major from "Student Table" where Age > 18 
Table name: _select_Student Table12, records: 17
                   record               First Name                      Age                    Major

                        0                    Faith                       19   Electrical Engineering
                        1                    Aidan                       19               Philosophy
                        2                    Avery                       20                Sociology
                        3                Johnathan                       20        Computer Sciences
                        4                    Riley                       20              Agriculture
                        5                    Aidan                       21                Sociology
                        6                    Avery                       21                Geography
                        7                   Wilson                       21        Computer Sciences
                        8                   Hailey                       22                      Law
                        9                   Wilson                       22                Economics
                       10                    Devon                       23                  Biology
                       11                  Ezekiel                       24                Economics
                       12                  Gregory                       25               Philosophy
                       13                     Miah                       26                Economics
                       14                    Vance                       27                  Biology
                       15                    Ariel                       28                 Divinity
                       16                    Vance                       29                Geography
Records selected: 17 19 4 15 18 8 10 16 9 14 0 1 6 7 11 5 3 

The command:  select "First Name", Age, Major from "Student Table" where Age <= 18 
Table name: _select_Student Table13, records: 3
                   record               First Name                      Age                    Major

                        0                    Lucia                       17                 Business
                        1                   Alaina                       18                  NOVALUE
                        2                    Dania                       18                  NOVALUE
Records selected: 12 2 13 

The command:  select "First Name", Age, Major from "Student Table" where Age >= 18 
Table name: _select_Student Table14, records: 19
                   record               First Name                      Age                    Major

                        0                   Alaina                       18                  NOVALUE
                        1                    Dania                       18                  NOVALUE
                        2                    Faith                       19   Electrical Engineering
                        3                    Aidan                       19               Philosophy
                        4                    Avery                       20                Sociology
                        5                Johnathan                       20        Computer Sciences
                        6                    Riley                       20              Agriculture
                        7                    Aidan                       21                Sociology
                        8                    Avery                       21                Geography
                        9                   Wilson                       21        Computer Sciences
                       10                   Hailey                       22                      Law
                       11                   Wilson                       22                Economics
                       12                    Devon                       23                  Biology
                       13                  Ezekiel                       24                Economics
                       14                  Gregory                       25               Philosophy
                       15                     Miah                       26                Economics
                       16                    Vance                       27                  Biology
                       17                    Ariel                       28                 Divinity
                       18                    Vance                       29                Geography
Records selected: 2 13 17 19 4 15 18 8 10 16 9 14 0 1 6 7 11 5 3 

The command:  select "First Name", Age, Major from "Student Table" where Age = 18 
Table name: _select_Student Table15, records: 2
                   record               First Name                      Age                    Major

                        0                   Alaina                       18                  NOVALUE
                        1                    Dania                       18                  NOVALUE
Records selected: 2 13 

The command:  select "First Name", Age, Major from "Student Table" where Age < 17 
Table name: _select_Student Table16, records: 0
                   record               First Name                      Age                    Major

Records selected: 

The command:  select "First Name", Age, Major from "Student Table" where Age > 50 
Table name: _select_Student Table17, records: 0
                   record               First Name                      Age                    Major

Records selected: 

The command:  select "First Name", Age, Major from "Student Table" where Age >= 100 
Table name: _select_Student Table18, records: 20
                   record               First Name                      Age                    Major

                        0                    Lucia                       17                 Business
                        1                   Alaina                       18                  NOVALUE
                        2                    Dania                       18                  NOVALUE
                        3                    Faith                       19   Electrical Engineering
                        4                    Aidan                       19               Philosophy
                        5                    Avery                       20                Sociology
                        6                Johnathan                       20        Computer Sciences
                        7                    Riley                       20              Agriculture
                        8                    Aidan                       21                Sociology
                        9                    Avery                       21                Geography
                       10                   Wilson                       21        Computer Sciences
                       11                   Hailey                       22                      Law
                       12                   Wilson                       22                Economics
                       13                    Devon                       23                  Biology
                       14                  Ezekiel                       24                Economics
                       15                  Gregory                       25               Philosophy
                       16                     Miah                       26                Economics
                       17                    Vance                       27                  Biology
                       18                    Ariel                       28                 Divinity
                       19                    Vance                       29                Geography
Records selected: 12 2 13 17 19 4 15 18 8 10 16 9 14 0 1 6 7 11 5 3 

The command:  select "First Name", Age, Major from "Student Table" where Age > 0 
Table name: _select_Student Table19, records: 20
                   record               First Name                      Age                    Major

                        0                    Lucia                       17                 Business
                        1                   Alaina                       18                  NOVALUE
                        2                    Dania                       18                  NOVALUE
                        3                    Faith                       19   Electrical Engineering
                        4                    Aidan                       19               Philosophy
                        5                    Avery                       20                Sociology
                        6                Johnathan                       20        Computer Sciences
                        7                    Riley                       20              Agriculture
                        8                    Aidan                       21                Sociology
                        9                    Avery                       21                Geography
                       10                   Wilson                       21        Computer Sciences
                       11                   Hailey                       22                      Law
                       12                   Wilson                       22                Economics
                       13                    Devon                       23                  Biology
                       14                  Ezekiel                       24                Economics
                       15                  Gregory                       25               Philosophy
                       16                     Miah                       26                Economics
                       17                    Vance                       27                  Biology
                       18                    Ariel                       28                 Divinity
                       19                    Vance                       29                Geography
Records selected: 12 2 13 17 19 4 15 18 8 10 16 9 14 0 1 6 7 11 5 3 

The command:  select "First Name", Age, Major from "Student Table" where Age >= 0 
Table name: _select_Student Table20, records: 20
                   record               First Name                      Age                    Major

                        0                    Lucia                       17                 Business
                        1                   Alaina                       18                  NOVALUE
                        2                    Dania                       18                  NOVALUE
                        3                    Faith                       19   Electrical Engineering
                        4                    Aidan                       19               Philosophy
                        5                    Avery                       20                Sociology
                        6                Johnathan                       20        Computer Sciences
                        7                    Riley                       20              Agriculture
                        8                    Aidan                       21                Sociology
                        9                    Avery                       21                Geography
                       10                   Wilson                       21        Computer Sciences
                       11                   Hailey                       22                      Law
                       12                   Wilson                       22                Economics
                       13                    Devon                       23                  Biology
                       14                  Ezekiel                       24                Economics
                       15                  Gregory                       25               Philosophy
                       16                     Miah                       26                Economics
                       17                    Vance                       27                  Biology
                       18                    Ariel                       28                 Divinity
                       19                    Vance                       29                Geography
Records selected: 12 2 13 17 19 4 15 18 8 10 16 9 14 0 1 6 7 11 5 3 

The command:  select * from "Student Table" where "First Name" = Aidan and Age = 19 
Table name: _select_Student Table21, records: 1
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                    Weber                       19               Philosophy
Records selected: 19 

The command:  select * from "Student Table" where "First Name" = Aidan and Age >= 19 
Table name: _select_Student Table22, records: 2
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                 Jacobson                       21                Sociology
                        1                    Aidan                    Weber                       19               Philosophy
Records selected: 8 19 

The command:  select * from "Student Table" where "First Name" = Aidan and Age > 19 
Table name: _select_Student Table23, records: 1
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                 Jacobson                       21                Sociology
Records selected: 8 

The command:  select * from "Student Table" where "First Name" = Aidan and Age <= 21 
Table name: _select_Student Table24, records: 2
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                 Jacobson                       21                Sociology
                        1                    Aidan                    Weber                       19               Philosophy
Records selected: 8 19 

The command:  select * from "Student Table" where "First Name" = Aidan and Age < 21 
Table name: _select_Student Table25, records: 1
                   record               First Name                Last Name                      Age                    Major

                        0                    Aidan                    Weber                       19               Philosophy
Records selected: 19 

The command:  select "First Name", Major from "Student Table" where "First Name" = Devon or Age > 20 and Major = "Computer Sciences" 
Table name: _select_Student Table26, records: 2
                   record               First Name                    Major

                        0                    Devon                  Biology
                        1                   Wilson        Computer Sciences
Records selected: 0 16 

The command:  select "First Name", Major from "Student Table" where "First Name" = Devon or Age >= 20 and Major = "Computer Sciences" 
Table name: _select_Student Table27, records: 3
                   record               First Name                    Major

                        0                    Devon                  Biology
                        1                Johnathan        Computer Sciences
                        2                   Wilson        Computer Sciences
Records selected: 0 15 16 

The command:  select "First Name", Major from "Student Table" where "First Name" = Aidan and Age = 21 and Major = "Computer Sciences" 
Table name: _select_Student Table28, records: 0
                   record               First Name                    Major

Records selected: 

The command:  select "First Name", Major from "Student Table" where "First Name" = Aidan or "First Name" = Wilson and Major = Economics 
Table name: _select_Student Table29, records: 3
                   record               First Name                    Major

                        0                    Aidan                Sociology
                        1                   Wilson                Economics
                        2                    Aidan               Philosophy
Records selected: 8 14 19 

The command:  select "First Name", Major from "Student Table" where "First Name" = Avery or "First Name" = Aidan and Major = Philosophy 
Table name: _select_Student Table30, records: 3
                   record               First Name                    Major

                        0                    Avery                Sociology
                        1                    Avery                Geography
                        2                    Aidan               Philosophy
Records selected: 4 10 19 

The command:  select "First Name", Age from "Student Table" where "First Name" = Vance and "First Name" = Hailey or "First Name" = Aidan and Age = 19 
Table name: _select_Student Table31, records: 1
                   record               First Name                      Age

                        0                    Aidan                       19
Records selected: 19 

The command:  select "First Name", "Last Name", Major from "Student Table" where "First Name" = Vance or "First Name" = Avery and "Last Name" = Adkins 
Table name: _select_Student Table32, records: 3
                   record               First Name                Last Name                    Major

                        0                    Vance                     Ward                Geography
                        1                    Avery                   Adkins                Sociology
                        2                    Vance                 Benjamin                  Biology
Records selected: 3 4 11 

The command:  select "First Name", Major from "Student Table" where "First Name" = Vance or "First Name" = Hailey or Major = Philosophy 
Table name: _select_Student Table33, records: 5
                   record               First Name                    Major

                        0                    Vance                Geography
                        1                  Gregory               Philosophy
                        2                   Hailey                      Law
                        3                    Vance                  Biology
                        4                    Aidan               Philosophy
Records selected: 3 6 9 11 19 

The command:  select "First Name", Major from "Student Table" where ( "First Name" = Ariel or "First Name" = Avery ) and Major = Divinity 
Table name: _select_Student Table34, records: 1
                   record               First Name                    Major

                        0                    Ariel                 Divinity
Records selected: 5 

The command:  select "First Name", Major from "Student Table" where ( "First Name" = Ariel or "First Name" = Avery ) or Major = Divinity 
Table name: _select_Student Table35, records: 3
                   record               First Name                    Major

                        0                    Avery                Sociology
                        1                    Ariel                 Divinity
                        2                    Avery                Geography
Records selected: 4 5 10 

The command:  select "First Name", Major from "Student Table" where ( "First Name" = Aidan or "First Name" = Wilson ) and Major = Economics 
Table name: _select_Student Table36, records: 1
                   record               First Name                    Major

                        0                   Wilson                Economics
Records selected: 14 

The command:  select "First Name", Major from "Student Table" where ( "First Name" = Avery or "First Name" = Aidan ) and Major = Philosophy 
Table name: _select_Student Table37, records: 1
                   record               First Name                    Major

                        0                    Aidan               Philosophy
Records selected: 19 

The command:  select "First Name", Age, Major from "Student Table" where "First Name" = Wilson and ( Major = "Computer Sciences" or Age = 22 or Age = 21 ) 
Table name: _select_Student Table38, records: 2
                   record               First Name                      Age                    Major

                        0                   Wilson                       22                Economics
                        1                   Wilson                       21        Computer Sciences

The command:  select "First Name", Age, Major from "Student Table" where "First Name" = Wilson or ( Major = "Computer Sciences" or Age = 22 ) 
Table name: _select_Student Table39, records: 4
                   record               First Name                      Age                    Major

                        0                   Hailey                       22                      Law
                        1                   Wilson                       22                Economics
                        2                Johnathan                       20        Computer Sciences
                        3                   Wilson                       21        Computer Sciences

The command:  select "First Name", Age, Major from "Student Table" where "First Name" = Wilson and ( Major = "Computer Sciences" or Age = 22 ) and Age = 21
Table name: _select_Student Table40, records: 1
                   record               First Name                      Age                    Major

                        0                   Wilson                       21        Computer Sciences

The command:  select 
Command ' select ' was invalid.

The command:  select * 
Command ' select * ' was invalid.

The command:  select * from 
Command ' select * from ' was invalid.

The command:  select "First Name", "Last Name", name from "Student Table" 
Field 'name' was invalid.

The command:  select "First Name", "Last Name" from "non-existant table"
'non-existant table' was an invalid table.

The command:  insert into "non-existant table" values a, b
'non-existant table' was an invalid table.

The command:  insert into "Student Table" values elan, nash, 20, cs, "450,000"
Values past 'cs' exceed the number of table columns.

The command:  select "First Name" from "Student Table" where  (and ("Last Name" = nash))
Missing operand.

The command:  select "First Name" from "Student Table" where  ("First Name" = elan) and "Last Name" = nash)
Missing left parenthesis.

The command:  select "First Name" from "Student Table" where  ("First Name" = elan) and ("Last Name" = nash
Missing right parenthesis.

The command:  select * from "Student Table" where "Last Name" = Nash and Department = 20 
Argument 'Department' was invalid.

The command:  make table "Student Table" fields first, last, age 
'Student Table' already exists.

[       OK ] TEST_SQL.TestSql (549 ms)
[ RUN      ] TEST_SQL.TestSqlBatchMode
//****************************************************************************
//              CREATE AND INSERT
//****************************************************************************

//---- employee table ----------
[0] make table employee fields  last,           first,                  dep
Table name: employee, records: 0
                   record                     last                    first                      dep


[1] insert into employee values Blow,           Joe,                    CS
Table name: employee, records: 1
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS

[2] insert into employee values Johnson,        "Jimmy",                Chemistry
Table name: employee, records: 2
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry

[3] insert into employee values Yang,           Bo,                     CS
Table name: employee, records: 3
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry
                        2                     Yang                       Bo                       CS

[4] insert into employee values "Jackson",      Billy,                  Math
Table name: employee, records: 4
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry
                        2                     Yang                       Bo                       CS
                        3                  Jackson                    Billy                     Math

[5] insert into employee values Johnson,        Billy,                  "Phys Ed"
Table name: employee, records: 5
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry
                        2                     Yang                       Bo                       CS
                        3                  Jackson                    Billy                     Math
                        4                  Johnson                    Billy                  Phys Ed

[6] insert into employee values "Van Gogh",     "Jim Bob",              "Phys Ed"
Table name: employee, records: 6
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry
                        2                     Yang                       Bo                       CS
                        3                  Jackson                    Billy                     Math
                        4                  Johnson                    Billy                  Phys Ed
                        5                 Van Gogh                  Jim Bob                  Phys Ed


[7] select * from employee 
Table name: _select_employee1, records: 6
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Johnson                    Jimmy                Chemistry
                        2                     Yang                       Bo                       CS
                        3                  Jackson                    Billy                     Math
                        4                  Johnson                    Billy                  Phys Ed
                        5                 Van Gogh                  Jim Bob                  Phys Ed


//----- student table ----------
[8] make table student fields   fname,                  lname,          major,                          age
Table name: student, records: 0
                   record                    fname                    lname                    major                      age


[9] insert into student values  Flo,                    Yao,            CS,                             20
Table name: student, records: 1
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20

[10] insert into student values         "Flo",                  "Jackson",      Math,                           21
Table name: student, records: 2
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21

[11] insert into student values         Calvin,                 Woo,            Physics,                        22
Table name: student, records: 3
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2                   Calvin                      Woo                  Physics                       22

[12] insert into student values         "Anna Grace",   "Del Rio",      CS,                                     22
Table name: student, records: 4
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2                   Calvin                      Woo                  Physics                       22
                        3               Anna Grace                  Del Rio                       CS                       22

[13] select * from student
Table name: _select_student3, records: 4
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2                   Calvin                      Woo                  Physics                       22
                        3               Anna Grace                  Del Rio                       CS                       22




//****************************************************************************
//              SIMPLE SELECT 
//****************************************************************************

[14] select * from student
Table name: _select_student4, records: 4
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2                   Calvin                      Woo                  Physics                       22
                        3               Anna Grace                  Del Rio                       CS                       22


//------- simple strings -------------------
[15] select * from student where lname = Jackson
Table name: _select_student5, records: 1
                   record                    fname                    lname                    major                      age

                        0                      Flo                  Jackson                     Math                       21


//----- quoted strings ---------------------
[16] select * from student where lname = "Del Rio"
Table name: _select_student6, records: 1
                   record                    fname                    lname                    major                      age

                        0               Anna Grace                  Del Rio                       CS                       22


//-------- non-existing string ------------------
[17] select * from student where lname = "Does Not Exist"
Table name: _select_student7, records: 0
                   record                    fname                    lname                    major                      age



//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[18] select * from student where lname > Yang
Table name: _select_student8, records: 1
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20



//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . . 
[19] select * from student where age > 50
Table name: _select_student9, records: 0
                   record                    fname                    lname                    major                      age



//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[20] select * from student where age  > 53
Table name: _select_student10, records: 0
                   record                    fname                    lname                    major                      age



//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . . 
[21] select * from student where age > 54
Table name: _select_student11, records: 0
                   record                    fname                    lname                    major                      age



//.................
//:Greater Equal  :
//.................
[22] select * from student where lname >= Yang
Table name: _select_student12, records: 1
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20

//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . . 
[23] select * from employee where last >= Jack
Table name: _select_employee13, records: 5
                   record                     last                    first                      dep

                        0                  Jackson                    Billy                     Math
                        1                  Johnson                    Jimmy                Chemistry
                        2                  Johnson                    Billy                  Phys Ed
                        3                 Van Gogh                  Jim Bob                  Phys Ed
                        4                     Yang                       Bo                       CS



//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . . 
[24] select * from student where lname < Jackson
Table name: _select_student14, records: 1
                   record                    fname                    lname                    major                      age

                        0               Anna Grace                  Del Rio                       CS                       22


//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[25] select * from student where age  < 20
Table name: _select_student15, records: 0
                   record                    fname                    lname                    major                      age




//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . . 

[26] select * from student where age  < 19
Table name: _select_student16, records: 0
                   record                    fname                    lname                    major                      age




//.................
//:Less Equal     :
//.................

[27] select * from student where lname <= Smith
Table name: _select_student17, records: 2
                   record                    fname                    lname                    major                      age

                        0               Anna Grace                  Del Rio                       CS                       22
                        1                      Flo                  Jackson                     Math                       21


//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . . 
[28] select * from employee where last <= Peach
Table name: _select_employee18, records: 4
                   record                     last                    first                      dep

                        0                     Blow                      Joe                       CS
                        1                  Jackson                    Billy                     Math
                        2                  Johnson                    Jimmy                Chemistry
                        3                  Johnson                    Billy                  Phys Ed


//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[29] select * from student where fname = "Flo" and lname = "Yao"
Table name: _select_student19, records: 1
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20



//.................
//:OR            :
//.................
[30] select * from student where fname = Flo or lname = Jackson
Table name: _select_student20, records: 2
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21



//.................
//:OR AND         :
//.................
[31] select * from student where fname = Flo or major = CS and age <= 23
Table name: _select_student21, records: 3
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2               Anna Grace                  Del Rio                       CS                       22



//.................
//:AND OR AND     :
//.................

[32] select * from student where age <30 and major=CS or major = Physics and lname = Jackson
Table name: _select_student22, records: 2
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1               Anna Grace                  Del Rio                       CS                       22



//.................
//:OR AND OR      :
//.................

[33] select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson 
Table name: _select_student23, records: 3
                   record                    fname                    lname                    major                      age

                        0                      Flo                      Yao                       CS                       20
                        1                      Flo                  Jackson                     Math                       21
                        2               Anna Grace                  Del Rio                       CS                       22

[       OK ] TEST_SQL.TestSqlBatchMode (0 ms)
[----------] 2 tests from TEST_SQL (549 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (549 ms total)
[  PASSED  ] 2 tests.
</pre>
