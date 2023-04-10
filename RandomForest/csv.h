#pragma once
#include "cnumpy.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception> 
#include <algorithm>
#include "type.h"
#include <cstdlib>


class CSV_reader {
private:
    static std::string remove_quote_from_name_column(std::string nameColumn){
        nameColumn.erase(std::remove(nameColumn.begin(), nameColumn.end(), '\"'), nameColumn.end());
        return nameColumn;
    }



public:



    static std::vector<std::string>  split(std::string s, std::string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }

    static std::vector<std::string> get_header(std::string line) {


        return split(line,",");
    }


    static bool is_int_number(std::string value){

        for(char x :value){
            if(!std::isdigit(x)){
                return false;
            }
        }
        return true;
    }

    static Type check_type(std::string value){

        if(is_int_number(value)){
            return Type::integer_type;
        }else if(is_double(value)){
            return Type::double_type;
        }else{
            return Type::string_type;
        }

    }

   static bool is_double(const std::string& s)
    {
        char* end = nullptr;
        double val = strtod(s.c_str(), &end);
        return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
    }


    static std::vector<Type> read_column_type(std::string firstDataLine){
        std::vector<std::string> columnValue = split(firstDataLine,",");
        std::vector<Type> typeColumn = std::vector<Type>();

        for(std::string val : columnValue){
            typeColumn.push_back(check_type(val));
        }

        return typeColumn;
    }


    static int how_many_lines_in_file(std::ifstream& inFile){

      return  std::count(std::istreambuf_iterator<char>(inFile),
                   std::istreambuf_iterator<char>(), '\n')+2;
    }



    static Cnumpy insert_data_to_cnumpy_from_file(Cnumpy & data,std::string filePath){

        std::string line;
        int x =0;
        int y=0;
        std::vector<Type> typeColumn = data.get_type_column();
        std::ifstream  file;
        file.open(filePath);
        getline(file, line);


        while (getline(file, line)) {


         //   std::cout<<"i="<<i<<" "<<line<<std::endl;
            std::vector<std::string> lines = split(line,",");

            for(std::string value :lines){

                std::string value2;
                if(value[0]=='.'){
                    value2="0"+value;
                }else{
                    value2 = value;
                }

            //    std::cout<<"["<<x<<","<<y<<"]"<<" = "<<value2<<std::endl;

              if(typeColumn[x] == Type::integer_type){
                   data.set_xy(x,y,std::stoi(value2));
               }else if (typeColumn[x] == Type::double_type){
                   data.set_xy(x,y,std::stod(value2));
               }else{
                   data.set_xy(x,y,value2);
               }

                x++;
            }
            x =0;

            y++;
        }

       // std::cout<<"Elo"<<std::endl;

        return data;

    }

	static Cnumpy read_csv_file_as_cnumpy(std::string path_to_file) {


        std::ifstream newfile(path_to_file);
        std::string tpx;


        std::vector<std::string> columnsName = std::vector<std::string>();

        if (getline(newfile, tpx)) {
            columnsName = get_header(tpx);
            std::cout<<tpx<<std::endl;
        }

        int columns_in_data = columnsName.size();

        std::vector<Type> columnType = std::vector<Type>();

        if (getline(newfile, tpx)) {
           // columns = get_header(tpx);
            columnType =read_column_type(tpx);

         //   std::cout<<tpx<<std::endl;
        }





        int rows_data = how_many_lines_in_file(newfile);
        std::cout<<"Ile wierszy : "<<rows_data<<std::endl;



        newfile.close();





       // double value = 2.0 ;
        Cnumpy data = Cnumpy(columns_in_data,rows_data,columnType,columnsName);

      //  data.set_xy(2,2,2.0);

       //std::cout<<data;


        Cnumpy result = insert_data_to_cnumpy_from_file(data,path_to_file);




       /* if (newfile.is_open()) {
            std::string tp;
            
            newfile.close(); 
        }
        else {
            std::cout << "blad";
           
        }*/

        return result;
	};
};
