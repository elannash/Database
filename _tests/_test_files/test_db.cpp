#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "../../includes/sql/sql.h"
#include "../../includes/stl_utils/vector_utilities.h"

using namespace std;

// the full table: Table name: Student Table, records: 21
//  record               First Name                Last Name                      Age                    Major

//       0                    Devon                     Vega                       23                  Biology
//       1                  Ezekiel                  Hensley                       24                Economics
//       2                   Alaina                   Vaughn                       18               Statistics
//       3                    Vance                     Ward                       29                Geography
//       4                    Avery                   Adkins                       20                Sociology
//       5                    Ariel                   Acosta                       28                 Divinity
//       6                  Gregory                   Sutton                       25               Philosophy
//       7                     Miah                  Mendoza                       26                Economics
//       8                    Aidan                 Jacobson                       21                Sociology
//       9                   Hailey                  Nielsen                       22                      Law
//      10                    Avery                    Bryan                       21                Geography
//      11                    Vance                 Benjamin                       27                  Biology
//      12                    Lucia                   Franco                       17                 Business
//      13                    Dania                    Hobbs                       18   Electrical Engineering
//      14                   Wilson                  Nichols                       22                Economics
//      15                Johnathan                   Wilcox                       20        Computer Sciences
//      16                   Wilson                   Knight                       21        Computer Sciences
//      17                    Faith                 Griffith                       19   Electrical Engineering
//      18                    Riley                   Larson                       20              Agriculture
//      19                    Aidan                    Weber                       19               Philosophy
//      20                     elan                     nash                  NOVALUE                  NOVALUE

const int MAKE_TABLE_COMMANDS = 0;
const int SELECT_TABLE_COMMANDS = 21;
const int EXCEPTION_TABLE_COMMANDS = 58;

vector<string> command_list{
    " create table \"Student Table\" fields \"First Name\", \"Last Name\", Age, Major",
    " insert into \"Student Table\" values Devon, Vega, 23, \"Biology\" ",
    " insert into \"Student Table\" values Ezekiel, Hensley, 24, \"Economics\" ",
    " insert into \"Student Table\" values Alaina, Vaughn, 18 ",
    " insert into \"Student Table\" values Vance, Ward, 29, \"Geography\" ",
    " insert into \"Student Table\" values Avery, Adkins, 20, \"Sociology\" ",
    " insert into \"Student Table\" values Ariel, Acosta, 28, \"Divinity\" ",
    " insert into \"Student Table\" values Gregory, Sutton, 25, \"Philosophy\" ",
    " insert into \"Student Table\" values Miah, Mendoza, 26, \"Economics\" ",
    " insert into \"Student Table\" values Aidan, Jacobson, 21, \"Sociology\" ",
    " insert into \"Student Table\" values Hailey, Nielsen, 22, \"Law\" ",
    " insert into \"Student Table\" values Avery, Bryan, 21, \"Geography\" ",
    " insert into \"Student Table\" values Vance, Benjamin, 27, \"Biology\" ",
    " insert into \"Student Table\" values Lucia, Franco, 17, \"Business\" ",
    " insert into \"Student Table\" values Dania, Hobbs, 18 ",
    " insert into \"Student Table\" values Wilson, Nichols, 22, \"Economics\" ",
    " insert into \"Student Table\" values Johnathan, Wilcox, 20, \"Computer Sciences\" ",
    " insert into \"Student Table\" values Wilson, Knight, 21, \"Computer Sciences\" ",
    " insert into \"Student Table\" values Faith, Griffith, 19, \"Electrical Engineering\" ",
    " insert into \"Student Table\" values Riley, Larson, 20, \"Agriculture\" ",
    " insert into \"Student Table\" values Aidan, Weber, 19, \"Philosophy\" ",

    " select * from \"Student Table\" ",
    " select * from \"Student Table\" where \"First Name\" = Aidan ",
    " select * from \"Student Table\" where \"First Name\" < Miah ",
    " select * from \"Student Table\" where \"First Name\" > Miah ",
    " select * from \"Student Table\" where \"First Name\" <= Miah ",
    " select * from \"Student Table\" where \"First Name\" >= Miah ",
    " select * from \"Student Table\" where \"Last Name\" < Mendoza ",
    " select * from \"Student Table\" where \"Last Name\" > Mendoza ",
    " select * from \"Student Table\" where \"Last Name\" <= Mendoza ",
    " select * from \"Student Table\" where \"Last Name\" >= Mendoza ",

    " select \"First Name\", Age, Major from \"Student Table\" where Age < 18 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age > 18 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age <= 18 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age >= 18 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age = 18 ",

    " select \"First Name\", Age, Major from \"Student Table\" where Age < 17 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age > 50 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age >= 100 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age > 0 ",
    " select \"First Name\", Age, Major from \"Student Table\" where Age >= 0 ",

    " select * from \"Student Table\" where \"First Name\" = Aidan and Age = 19 ",
    " select * from \"Student Table\" where \"First Name\" = Aidan and Age >= 19 ",
    " select * from \"Student Table\" where \"First Name\" = Aidan and Age > 19 ",
    " select * from \"Student Table\" where \"First Name\" = Aidan and Age <= 21 ",
    " select * from \"Student Table\" where \"First Name\" = Aidan and Age < 21 ",

    " select \"First Name\", Major from \"Student Table\" where \"First Name\" = Devon or Age > 20 and Major = \"Computer Sciences\" ",
    " select \"First Name\", Major from \"Student Table\" where \"First Name\" = Devon or Age >= 20 and Major = \"Computer Sciences\" ",
    " select \"First Name\", Major from \"Student Table\" where \"First Name\" = Aidan and Age = 21 and Major = \"Computer Sciences\" ",
    " select \"First Name\", Major from \"Student Table\" where \"First Name\" = Aidan or \"First Name\" = Wilson and Major = Economics ",
    " select \"First Name\", Major from \"Student Table\" where \"First Name\" = Avery or \"First Name\" = Aidan and Major = Philosophy ",
    " select \"First Name\", Age from \"Student Table\" where \"First Name\" = Vance and \"First Name\" = Hailey or \"First Name\" = Aidan and Age = 19 ",
    " select \"First Name\", \"Last Name\", Major from \"Student Table\" where \"First Name\" = Vance or \"First Name\" = Avery and \"Last Name\" = Adkins ",
    " select \"First Name\", Major from \"Student Table\" where \"First Name\" = Vance or \"First Name\" = Hailey or Major = Philosophy ",

    " select \"First Name\", Major from \"Student Table\" where ( \"First Name\" = Ariel or \"First Name\" = Avery ) and Major = Divinity ",
    " select \"First Name\", Major from \"Student Table\" where ( \"First Name\" = Ariel or \"First Name\" = Avery ) or Major = Divinity ",
    " select \"First Name\", Major from \"Student Table\" where ( \"First Name\" = Aidan or \"First Name\" = Wilson ) and Major = Economics ",
    " select \"First Name\", Major from \"Student Table\" where ( \"First Name\" = Avery or \"First Name\" = Aidan ) and Major = Philosophy ",
    " select \"First Name\", Age, Major from \"Student Table\" where \"First Name\" = Wilson and ( Major = \"Computer Sciences\" or Age = 22 or Age = 21 ) ",
    " select \"First Name\", Age, Major from \"Student Table\" where \"First Name\" = Wilson or ( Major = \"Computer Sciences\" or Age = 22 ) ",
    " select \"First Name\", Age, Major from \"Student Table\" where \"First Name\" = Wilson and ( Major = \"Computer Sciences\" or Age = 22 ) and Age = 21",

    " select ",
    " select * ",
    " select * from ",
    " select \"First Name\", \"Last Name\", name from \"Student Table\" ",
    " select \"First Name\", \"Last Name\" from \"non-existant table\"",
    " insert into \"non-existant table\" values a, b",
    " insert into \"Student Table\" values elan, nash, 20, cs, \"450,000\"",
    " select \"First Name\" from \"Student Table\" where  (and (\"Last Name\" = nash))",
    " select \"First Name\" from \"Student Table\" where  ((\"Last Name\" = nash) or)",
    " select \"First Name\" from \"Student Table\" where  (\"First Name\" = elan) and \"Last Name\" = nash)",
    " select \"First Name\" from \"Student Table\" where  (\"First Name\" = elan) and (\"Last Name\" = nash",
    " select * from \"Student Table\" where \"Last Name\" = Nash and Department = 20 ",
    " make table \"Student Table\" fields first, last, age ",
};

vector<vector<long> > select_recnos{
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
    {8, 19},
    {8, 19, 2, 5, 4, 10, 13, 0, 1, 17, 6, 9, 15, 12},
    {18, 3, 11, 14, 16},
    {8, 19, 2, 5, 4, 10, 13, 0, 1, 17, 6, 9, 15, 12, 7},
    {7, 18, 3, 11, 14, 16},
    {5, 4, 11, 10, 12, 17, 1, 13, 8, 16, 18},
    {14, 9, 6, 2, 0, 3, 19, 15},
    {5, 4, 11, 10, 12, 17, 1, 13, 8, 16, 18, 7},
    {7, 14, 9, 6, 2, 0, 3, 19, 15},
    {12},
    {17, 19, 4, 15, 18, 8, 10, 16, 9, 14, 0, 1, 6, 7, 11, 5, 3},
    {12, 2, 13},
    {2, 13, 17, 19, 4, 15, 18, 8, 10, 16, 9, 14, 0, 1, 6, 7, 11, 5, 3},
    {2, 13},
    {},
    {},
    {12, 2, 13, 17, 19, 4, 15, 18, 8, 10, 16, 9, 14, 0, 1, 6, 7, 11, 5, 3},
    {12, 2, 13, 17, 19, 4, 15, 18, 8, 10, 16, 9, 14, 0, 1, 6, 7, 11, 5, 3},
    {12, 2, 13, 17, 19, 4, 15, 18, 8, 10, 16, 9, 14, 0, 1, 6, 7, 11, 5, 3},
    {19},
    {8, 19},
    {8},
    {8, 19},
    {19},
    {0, 16},
    {0, 15, 16},
    {},
    {8, 14, 19},
    {4, 10, 19},
    {19},
    {3, 4, 11},
    {3, 6, 9, 11, 19},
    {5},
    {4, 5, 10},
    {14},
    {19},
    {14, 16},
    {9, 14, 15, 16},
    {16},
};

bool test_sql(bool debug = false)
{
  // uncomment exception throws in sql, table, rpn
  // uncomment if condition in table
  // delete if condition in token eval function
  // uncomment assert in token eval function

  SQL sql;

  for (int i = MAKE_TABLE_COMMANDS; i < SELECT_TABLE_COMMANDS; i++)
  {
    cout << "The command: " << command_list[i] << endl;

    try
    {
      cout << sql.command(command_list[i]);
    }
    catch (const exception &e)
    {
      cerr << e.what() << '\n';
    }
  }

  for (int i = SELECT_TABLE_COMMANDS; i < EXCEPTION_TABLE_COMMANDS; i++)
  {
    bool recnos_match;

    cout << "The command: " << command_list[i] << endl;

    try
    {
      cout << sql.command(command_list[i]);
      cout << "Records selected: " << sql.select_recnos() << endl
           << endl;
    }
    catch (const exception &e)
    {
      cerr << e.what() << endl;
    }

    // records match if size is the same and contents are in the same order
    recnos_match = (select_recnos[i - SELECT_TABLE_COMMANDS].size() == sql.select_recnos().size()) && (equal(select_recnos[i - SELECT_TABLE_COMMANDS].begin(), select_recnos[i - SELECT_TABLE_COMMANDS].end(), sql.select_recnos().begin()));
    if (!recnos_match)
    {
      cout << "Selected record numbers did not match expected record numbers." << endl
           << setw(10) << "Expected: " << select_recnos[i - SELECT_TABLE_COMMANDS] << endl
           << setw(10) << "Found: " << sql.select_recnos() << endl;
      return false;
    }
  }

  for (int i = EXCEPTION_TABLE_COMMANDS; i < command_list.size(); i++)
  {
    cout << "The command: " << command_list[i] << endl;

    try
    {
      cout << sql.command(command_list[i]);
    }
    catch (const exception &e)
    {
      cerr << e.what() << endl;
    }
  }

  return true;
}

bool test_sql_batch(bool debug = false)
{
  char *filename = "batch_commands.txt";
  SQL sql; // can also pass filename into ctor and it will execute commands. though, sql class may throw exceptions.

  try
  {
    sql.batch_mode(filename);
  }
  catch (const exception &e)
  {
    cerr << e.what() << endl;
  }

  return true;
}

TEST(TEST_SQL, TestSql)
{
  EXPECT_EQ(1, test_sql(false));
}

TEST(TEST_SQL, TestSqlBatchMode)
{
  EXPECT_EQ(1, test_sql_batch(false));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
