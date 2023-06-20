/*
 * main.cc
 *
 *  Created on: Mar 10, 2021
 *      The main program in the file main.cc
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <string>
#include "util.cc"
#include "hash.cc"
using namespace std;
int main(int argc, char **argv) {
  int num_app_categories, num_of_apps, num_of_queries;
  string line;
  getline(cin, line);  // Read number of app categories
  num_app_categories = atoi(line.c_str());
  categories *app_categories = new categories[num_app_categories
      * sizeof(categories)];
  // Read categories name
  for (int i = 0; i < num_app_categories; i++) {
    // Read name of categories
    getline(cin, line);
    strcpy(app_categories[i].category, line.c_str());
    app_categories[i].root = NULL;
  }
  getline(cin, line);  // Read num of apps
  num_of_apps = atoi(line.c_str());
  int hash_table_size = calculate_hash_table_size(num_of_apps);
  hash_table_entry **hash_table = new hash_table_entry*[hash_table_size
      * sizeof(hash_table_entry)];
  for (int i = 0; i < hash_table_size; i++)
    hash_table[i] = NULL;
  for (int i = 0; i < num_of_apps; i++) {
    app_info *app_info_tmp = new app_info[sizeof(app_info)];
    cin.getline(app_info_tmp->category, CAT_NAME_LEN);
    cin.getline(app_info_tmp->app_name, APP_NAME_LEN);
    cin.getline(app_info_tmp->version, VERSION_LEN);
    getline(cin, line);
    app_info_tmp->size = atof(line.c_str());
    cin.getline(app_info_tmp->units, UNIT_SIZE);
    getline(cin, line);
    app_info_tmp->price = atof(line.c_str());
    bst *bst_tree = new bst[sizeof(bst)];
    bst_tree->record = *app_info_tmp;
    bst_tree->right = NULL;
    bst_tree->left = NULL;
    for (int i = 0; i < num_app_categories; i++) {
      if (strcmp(bst_tree->record.category, app_categories[i].category) == 0) {
        app_categories[i].root = append_bts_with_other(app_categories[i].root,
                                                       bst_tree);
      }
    }
    insert_bst_to_hash(hash_table, bst_tree, hash_table_size);
  }  // Finished reading data

  // Read the query

  getline(cin, line);
  num_of_queries = atoi(line.c_str());

  string queries_list[num_of_queries];
  for (int i = 0; i < num_of_queries; i++) {
    getline(cin, queries_list[i]);
  }
  // Select and process each query
  int queries_ind = 0;
  int query_type = -1;
  bool reportCommand = false;
  while (queries_ind < num_of_queries) {
    string query = queries_list[queries_ind];
    query_type = type_of_query(query);
    cout << query << endl;
    if (query_type == 1) {
      // find app
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      bst *categories_in_table = search_bst_with_name(hash_table,
                                                      categories_name.c_str(),
                                                      hash_table_size);
      if (categories_in_table == NULL)
        cout << "\tApplication " << categories_name << " not found." << endl;
      else {
        cout << "\tFound Application: " << categories_name << endl;
        print_app_info(categories_in_table->record);
      }
    }
    // find max price apps <category>
    else if (query_type == 2) {
      // Get input category from the query
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      // Process Query with <inputCategory>
      int instruction = 0;
      int catNum;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, categories_name.c_str()) == 0) {
          if (app_categories[i].root == NULL)
            instruction = 1;
          else {
            instruction = 2;
            catNum = i;
          }
        }
      }
      if (instruction == 0) {
        cout << "\tCategory " << categories_name << " not found." << endl;
      } else if (instruction == 1) {
        cout << "\tCategory " << categories_name << " no apps found." << endl;
      } else {
        cout << "\tCategory: " << categories_name << endl;
        find_max_price(app_categories[catNum].root);
      }
    }
    // print-apps <category>
    else if (query_type == 3) {
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      int instruction = 0;
      int catNum;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, categories_name.c_str()) == 0) {
          if (app_categories[i].root == NULL)
            instruction = 1;
          else {
            instruction = 2;
            catNum = i;
          }
        }
      }
      if (instruction == 0) {
        cout << "\tCategory " << categories_name << " not found." << endl;
      } else if (instruction == 1) {
        cout << "\tCategory " << categories_name << " no apps found." << endl;
      } else {
        cout << "\tCategory: " << categories_name << endl;
        print_the_query(app_categories[catNum].root);
      }
    }
    // find price free <category>
    else if (query_type == 4) {
      // Get input category from the query
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      int instruction = 0;
      int catNum;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, categories_name.c_str()) == 0) {
          if (app_categories[i].root == NULL)
            instruction = 1;
          else {
            instruction = 2;
            catNum = i;
          }
        }
      }
      if (instruction == 0) {
        cout << "\tCategory " << categories_name << " not found." << endl;
      } else if (instruction == 1) {
        cout << "\tCategory " << categories_name << " no free apps found."
             << endl;
      } else {
        cout << "\tFree apps in Category: " << categories_name << endl;
        float price = 0;
        print_app_name_with_price(app_categories[catNum].root, price);
      }
    }
    // range <category> price <low> <high>
    else if (query_type == 5) {
      // Get input category from the query
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      if (categories_name.empty())
        categories_name = "EMPTY";
      int start_range = query.find('e', end_of_categories + 1) + 1;
      int eng_range = query.find('\n', start_range + 1);
      int range_length = eng_range - start_range;
      string range_str = query.substr(start_range, range_length);
      float low, high;
      sscanf(range_str.c_str(), "%f %f", &low, &high);
      int instruction = 0;
      int categories_ind;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, categories_name.c_str()) == 0) {
          if (app_categories[i].root == NULL)
            instruction = 1;
          else {
            instruction = 2;
            categories_ind = i;
          }
        }
      }
      if (instruction == 0)
        cout << "\tCategory " << categories_name << " not found." << endl;
      else if (instruction == 1) {
        cout << "\tNo applications found in " << categories_name
             << " for the given price range (" << low << "," << high << ")"
             << endl;
      } else {
        bool is_valid_range = print_app_name_in_range_price(
            app_categories[categories_ind].root, low, high);
        if (is_valid_range) {
          cout << "\tNo applications found in " << categories_name
               << " for the given price range (" << low << "," << high << ")"
               << endl;
        }
      }
    }
    // range <category> name <low> <high>
    else if (query_type == 6) {
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      if (categories_name.empty())
        categories_name = "EMPTY";
      // Get input low from the query
      int low_range_start = query.find('\"', end_of_categories + 1) + 1;
      int low_range_end = query.find('\"', low_range_start);
      int low_length = low_range_end - low_range_start;
      string low_str = query.substr(low_range_start, low_length);
      char low = '~';
      if (!low_str.empty())
        low = low_str.at(0);
      int high_range_start = query.find('\"', low_range_end + 1) + 1;
      int high_range_end = query.find('\"', high_range_start);
      int high_length = high_range_end - high_range_start;
      string high_str = query.substr(high_range_start, high_length);
      char high = '~';
      if (!high_str.empty())
        high = high_str.at(0);
      int instruction = 0;
      int catNum;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, categories_name.c_str()) == 0) {
          if (app_categories[i].root == NULL)
            instruction = 1;
          else {
            instruction = 2;
            catNum = i;
          }
        }
      }
      if (instruction == 0)
        cout << "\tCategory " << categories_name << " not found." << endl;
      else if (instruction == 1) {
        cout << "\tNo applications found in " << categories_name
             << " for the given range (" << low << "," << high << ")" << endl;
      } else {
        bool is_valid_range = print_app_name_in_range_name(
            app_categories[catNum].root, low, high);
        if (is_valid_range) {
          cout << "\tNo applications found in " << categories_name
               << " for the given range (" << low << "," << high << ")" << endl;
        }
      }
    }
    // delete <category> <app_name>
    else if (query_type == 7) {
      int start_of_categories = query.find('\"') + 1;
      int end_of_categories = query.find('\"', start_of_categories);
      int categories_length = end_of_categories - start_of_categories;
      string categories_name = query.substr(start_of_categories,
                                            categories_length);
      if (categories_name.empty())
        categories_name = "EMPTY";
      int start_name_str = query.find('\"', end_of_categories + 1) + 1;
      int end_name_str = query.find('\"', start_name_str);
      int name_length = end_name_str - start_name_str;
      string name_str = query.substr(start_name_str, name_length);
      if (name_str.empty())
        name_str = "EMPTY";
      bool not_exist = true;
      int catNum;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, categories_name.c_str()) == 0) {
          not_exist = false;
          catNum = i;
        }
      }
      if (not_exist) {
        cout << "\tApplication " << name_str << " not found in category "
             << categories_name << "; unable to delete." << endl;
      } else {
        bool deleted = delete_table(hash_table, hash_table_size,
                                    name_str.c_str(), categories_name.c_str());
        app_categories[catNum].root = remove_node(name_str.c_str(),
                                                  app_categories[catNum].root);
        if (deleted) {
          cout << "\tApplication " << name_str << " from Category "
               << categories_name << " successfully deleted." << endl;
        } else {
          cout << "\tApplication " << name_str << " not found in category "
               << categories_name << "; unable to delete." << endl;
        }
      }
    } else if (query_type == 8)
      reportCommand = false;
    else if (query_type == 9)
      reportCommand = true;
    else {
      cout << "\t--invalid query #" << queries_ind + 1 << "--" << endl;
    }
    cout << endl;
    queries_ind++;
  }

  // Report Output
  if (reportCommand) {
    cout << "BST Statistics" << endl;
    cout << "\tNumber of Categories: " << num_app_categories << endl;
    for (int i = 0; i < num_app_categories; i++) {
      cout << "\t" << app_categories[i].category << endl;
      int totalCount = size_of_bst(app_categories[i].root);
      cout << "\t\tTotal Nodes: " << totalCount << endl;
      int height = get_height_bst(app_categories[i].root);
      cout << "\t\tHeight: " << height << endl;
      if (totalCount == 0) {
        cout << "\t\tNo Nodes Exist." << endl;
      } else if (height == 0) {
        cout << "\t\tNo Subtrees Exist." << endl;
      } else {
        int heightL = get_height_bst(app_categories[i].root->left);
        cout << "\t\tHeight of Left Subtree: " << heightL << endl;
        int heightR = get_height_bst(app_categories[i].root->right);
        cout << "\t\tHeight of Right Subtree: " << heightR << endl;
      }
    }

    cout << "\nHash Table Statistics" << endl;
    double hash_m = hash_table_size;
    double hash_n = 0;
    int chainLength[num_of_apps + 1];
    int maxLength;
    for (int i = 0; i <= num_of_apps; i++) {
      chainLength[i] = count_hash_with_length(hash_table, hash_table_size, i);
      if (chainLength[i] > 0)
        maxLength = i;
    }
    cout << "\tChain Length\t# of Lists" << endl;
    for (int length = 0; length <= maxLength; length++) {
      cout << "\t\t" << length << "\t\t" << chainLength[length] << endl;

      hash_n = hash_n + length * chainLength[length];
    }
    cout << "\tMax Length = " << maxLength << endl;
    cout << "\tn = " << hash_n << endl;
    cout << "\tm = " << hash_m << endl;
    double alpha = hash_n / hash_m;
    printf("\tLoad Factor = %.3f\n", alpha);
    char *query_name = new char[APP_NAME_LEN];
    strcpy(query_name, "Fit Men Cook");
    cout << "\nfind app \"" << query_name << "\" Running Time Comparison:"
         << endl;
    auto start = std::chrono::system_clock::now();
    bst *hash_return = search_bst_with_name(hash_table, query_name,
                                            hash_table_size);
    auto end = std::chrono::system_clock::now();
    auto hash_time = std::chrono::duration<double, nano>(end - start);
    char *category = hash_return->record.category;
    if (category != NULL) {
      auto start2 = std::chrono::system_clock::now();
      int categoryIndex = -1;
      for (int i = 0; i < num_app_categories; i++) {
        if (strcmp(app_categories[i].category, category) == 0)
          categoryIndex = i;
      }
      if (categoryIndex == -1)
        cout << "\tCategory " << category << " not found." << endl;
      auto end2 = std::chrono::system_clock::now();
      auto bst_time = std::chrono::duration<double, nano>(end2 - start2);
      cout << "\tHash Table Running Time: " << hash_time.count()
           << " nanoseconds" << endl;
      cout << "\tBinary Search Tree Running Time: " << bst_time.count()
           << " nanoseconds" << endl;
    } else {
      cout << "\tApplication " << query_name << " not found." << endl;
    }
  }

  for (int i = 0; i < num_app_categories; i++) {
    if (app_categories[i].root != NULL)
      app_categories[i].root = free_bst(app_categories[i].root);
  }
  delete[] app_categories;
  for (int j = 0; j < hash_table_size; j++) {
    while (hash_table[j] != NULL) {
      hash_table_entry *tempEntry;
      tempEntry = hash_table[j];
      hash_table[j] = hash_table[j]->next;
      delete[] tempEntry;
    }
  }
  delete[] hash_table;

  return 0;
}
