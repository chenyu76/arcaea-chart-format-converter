#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

struct command
{
    bool converted;
    string name;
    vector<string> parameter;
    vector<string> arctap;
};


class _aff_file
{
    public:
        _aff_file(string);
        virtual ~_aff_file();

        void arc_skyline(); //将arc转成skyline
        void skyline_arc(char color = 'A'); //color 0蓝,1红,2绿 A自动
        void hold_arc();
        void hold_skyline();
        void tap_arctap();
        void tap_skyline();
        void arctap_skyline();
        void remove_(string);
        void add_a_note();

        void set_convertd_0();

        void mix_chart(string filename = "1.aff");

        void export_aff(string filename = "a.aff");

    protected:

    private:
        unsigned int m_Counter;
        string AudioOffset;
        string Timing;
        vector<command> commands;
};

string get_filename(string);

int main()
{
    system("chcp 65001");
    system("color fc");
    system("cls");


    cout << "读取文件" << endl;
    string filename = "2.aff";
    filename = get_filename(filename);
    _aff_file aff_file(filename);
    string choose = "1";
    while(true)
    {
        system("cls");
        cout << "读取了文件" << filename << endl
            << "你想做什么？" << endl
            << "x. 不保存退出" << endl
            << "0. 退出并保存" << endl
            << "1. 全部转换成skyline" << endl
            << "2. 全部转换成arc" << endl
            << "3. 混合另一个谱面" << endl
            << "----以下是杂项----" << endl
            << "A. 将arc转成skyline" << endl
            << "B. 将skyline转成arc" << endl
            << "C. 将地面note转成skyline" << endl
            << "D. 将地面hold转成skyline" << endl
            << "E. 将天空note转成skyline" << endl
            << "F. 在歌曲最前面添加一个note" << endl
            //<< "G. 删除指定类型的元素" << endl
            << " " << endl;


        cout << "输入选择：";
        getline(cin, choose);
        switch(choose[0])
        {
        case 'x':
            {
                return 0;
            }
        case '0':
            {
                cout << "保存文件" << endl;
                filename = get_filename(filename);
                aff_file.export_aff(filename);
                cout << "文件保存到了" << filename << endl;
                system("pause");
                return 0;
            }
        case '1':
            {
                aff_file.arc_skyline();
                aff_file.hold_skyline();
                aff_file.tap_skyline();
                aff_file.arctap_skyline();
                cout << "注意：现在谱面里的物量为零," << endl
                    << "你可能需要使用F选项添加一个" << endl;
                break;
            }
        case '2':
            {
                //aff_file.arc_skyline();
                aff_file.hold_skyline();
                aff_file.tap_skyline();
                aff_file.arctap_skyline();
                aff_file.set_convertd_0();
                cout << "生成为什么颜色的arc？" << endl
                    << "0. 全是蓝的" << endl
                    << "1. 全是红的" << endl
                    << "2. 全是绿的" << endl
                    << "A. 自动选择" << endl
                    << "输入选择：";
                string color_choose;
                getline(cin, color_choose);

                aff_file.skyline_arc(color_choose[0]);
                break;
            }
        case '3':
            {
                string mix_filename = "1.aff";
                mix_filename = get_filename(mix_filename);
                aff_file.mix_chart(mix_filename);
                break;
            }
        case 'A':
        case 'a':
            {
                aff_file.arc_skyline();
                break;
            }
        case 'B':
        case 'b':
            {
                cout << "将skyline转成什么颜色" << endl
                    << "0. 全是蓝的" << endl
                    << "1. 全是红的" << endl
                    << "2. 全是绿的" << endl
                    << "A. 自动选择" << endl
                    << "输入选择：";
                string color_choose;
                getline(cin, color_choose);

                aff_file.skyline_arc(color_choose[0]);
                break;
            }
        case 'C':
        case 'c':
            {
                aff_file.tap_skyline();
                break;
            }
        case 'D':
        case 'd':
            {
                aff_file.hold_skyline();
                break;
            }
        case 'E':
        case 'e':
            {
                aff_file.arctap_skyline();
                break;
            }
        case 'F':
        case 'f':
            {
                aff_file.add_a_note();
                break;
            }
        case 'G':
        case 'g':
            {
                cout << "删除什么？" << endl
                    << "可选项: note, hold, arctap, skyline, arc" << endl
                    << "输入你的选择";
                getline(cin, choose);
                aff_file.remove_(choose);
            }
        default:
            cout << "错误的选择，请重试" << endl;
        }
        cout << "操作已完成，按回车继续" << endl;
        getline(cin, choose);
    }
}


string get_filename(string default_filename)
{
    string str;
    cout << "输入文件名(默认为" << default_filename << "):";
    getline(cin, str);
    if(str[0] == '"')
        str = str.substr(1, str.size() - 2);
    if(str != "")
        return str;
    return default_filename;
}



_aff_file::_aff_file(string filename)
{
    //ctor
    cout << "filename=" << filename << endl;
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
    {
        cout << "文件打开出错，请检查文件是否存在" << endl;;
        system("pause");
        exit (1);
    }


    string tmp_str;
    infile >> this->AudioOffset;
    infile >> tmp_str;  //读入 -
    infile >> this->Timing;
    while(!infile.eof())
    {
        infile >> tmp_str;
        if(!infile)
            break;

        //cout << tmp_str << endl;
        command tmp_cmd;

        int i = 0;
        if(tmp_str[0] == '(')
        {
            tmp_cmd.name = "tap";
        }
        else
        {
            while(tmp_str[i] != '(')
            {
                if(i >= tmp_str.size())
                    break;
                i += 1;
            }
            tmp_cmd.name = tmp_str.substr(0, i);
        }
        //cout << "tmp_cmd.name="<< tmp_cmd.name << endl;

        i += 1;
        int ii = 0;
        while(!(tmp_str[i + ii] == ';'||tmp_str[i + ii] == '['))
        {
            //cout << tmp_str[i + ii] << endl;
            //cout << i << "\tii="<< ii<< endl;
            if(i + ii >= tmp_str.size())
                break;
            while(!(tmp_str[i + ii] == ','|| tmp_str[i + ii] == ')' || tmp_str[i + ii] == ';'))
            {
                if(i + ii >= tmp_str.size())
                    break;
                ii += 1;
            }
            tmp_cmd.parameter.push_back(tmp_str.substr(i, ii));
            //cout << "tmp_cmd.parameter.push_back(tmp_str.substr(i, ii))=" <<  tmp_str.substr(i, ii) << endl;
            i += ii + 1;
            ii = 0;
        }
        if(tmp_str[i + ii] == '[')
        {
            i += 1;
            while(tmp_str[i + ii] != ';')
            {
                if(i + 7 > tmp_str.size())
                    break;
                if(tmp_str.substr(i, 7) == "arctap(")
                {
                    i += 7;
                    while(!(tmp_str[i + ii] == ')'|| tmp_str[i + ii] == ']' || tmp_str[i + ii] == ';'))
                    {
                        if(i + ii >= tmp_str.size())
                            break;
                        ii += 1;
                    }
                    tmp_cmd.arctap.push_back(tmp_str.substr(i, ii));
                    //cout << "tmp_cmd.arctap.push_back(tmp_str.substr(i, ii))=" << tmp_str.substr(i, ii) << endl;

                    i += ii;
                    ii = 0;
                    while(!(tmp_str.substr(i + ii, 7) == "arctap(" || tmp_str[i + ii] == ';'))
                    {
                        if(i + ii >= tmp_str.size())
                            break;
                        ii += 1;
                    }
                    i += ii;
                    ii = 0;
                }
            }
        }
        tmp_cmd.converted = false;
        this->commands.push_back(tmp_cmd);
    }
    infile.close();
}

_aff_file::~_aff_file()
{
    //dtor
}


void _aff_file::set_convertd_0()
{
    for(int i = 0; i < commands.size(); i++)
    {
        commands[i].converted = 0;
    }
}

void _aff_file::mix_chart(string filename)
{
    _aff_file tmp_aff_file(filename);
    for(int i = 0; i < tmp_aff_file.commands.size(); i++)
    {
        this->commands.push_back(tmp_aff_file.commands[i]);
    }

}


void _aff_file::add_a_note()
{
    command tmp_cmd;
    tmp_cmd.name = "tap";
    tmp_cmd.converted = true;
    tmp_cmd.parameter.push_back("0");
    tmp_cmd.parameter.push_back("1");
    commands.push_back(tmp_cmd);
}


void _aff_file::arc_skyline()
{
    for(int i = 0; i < this->commands.size(); i++)
    {
        if(!this->commands[i].converted)
        {
            if(this->commands[i].name == "arc" && this->commands[i].parameter[9] == "false")
            {
                this->commands[i].parameter[9] = "true";
                this->commands[i].converted = true;
            }
        }
    }
}
void _aff_file::skyline_arc(char color)
{
    for(int i = 0; i < this->commands.size(); i++)
    {
        if(!this->commands[i].converted)
        {
            if(this->commands[i].name == "arc" && this->commands[i].parameter[9] == "true")
            {
                this->commands[i].parameter[9] = "false";
                switch(color)
                {
                case 'A':
                    {
                        if(stod(commands[i].parameter[3]) > 0.5)
                            this->commands[i].parameter[7] = "1";
                        else if(stod(commands[i].parameter[3]) < 0.5)
                            this->commands[i].parameter[7] = "0";
                        else
                            this->commands[i].parameter[7] = "2";
                        break;
                    }
                case '0':
                    this->commands[i].parameter[7] = "0";
                    break;
                case '1':
                    this->commands[i].parameter[7] = "1";
                    break;
                case '2':
                    this->commands[i].parameter[7] = "2";
                    break;

                }
                this->commands[i].arctap.clear();
                this->commands[i].converted = true;
            }
        }
    }
}

//void _aff_file::hold_arc();
void _aff_file::hold_skyline()
{
    for(int i = 0; i < this->commands.size(); i++)
    {
        if(!this->commands[i].converted)
        {
            if(this->commands[i].name == "hold")
            {
                switch(commands[i].parameter[2][0])
                {
                case '1':
                    this->commands[i].parameter[2] = "-0.25";
                    this->commands[i].parameter.push_back("-0.25");
                    break;
                case '2':
                    this->commands[i].parameter[2] = "0.25";
                    this->commands[i].parameter.push_back("0.25");
                    break;
                case '3':
                    this->commands[i].parameter[2] = "0.75";
                    this->commands[i].parameter.push_back("0.75");
                    break;
                case '4':
                    this->commands[i].parameter[2] = "1.25";
                    this->commands[i].parameter.push_back("1.25");
                    break;
                }
                string param[6] = {"s", "0.00", "0.00", "0", "none", "true"};
                for(int j = 0; j < 6; j++)
                    this->commands[i].parameter.push_back(param[j]);
                this->commands[i].name = "arc";
                this->commands[i].converted = true;
            }
        }
    }
}
//void _aff_file::tap_arctap();
void _aff_file::tap_skyline()
{
    for(int i = 0; i < this->commands.size(); i++)
    {
        if(!this->commands[i].converted)
        {
            if(this->commands[i].name == "tap")
            {
                this->commands[i].parameter.push_back(this->commands[i].parameter[1]);
                this->commands[i].parameter[1] = this->commands[i].parameter[0];
                switch(commands[i].parameter[2][0])
                {
                case '1':
                    this->commands[i].parameter[2] = "-0.50";
                    this->commands[i].parameter.push_back("0.00");
                    break;
                case '2':
                    this->commands[i].parameter[2] = "0.00";
                    this->commands[i].parameter.push_back("0.50");
                    break;
                case '3':
                    this->commands[i].parameter[2] = "0.50";
                    this->commands[i].parameter.push_back("1.00");
                    break;
                case '4':
                    this->commands[i].parameter[2] = "1.00";
                    this->commands[i].parameter.push_back("1.50");
                    break;
                }
                string param[6] = {"s", "0.00", "0.00", "0", "none", "true"};
                for(int j = 0; j < 6; j++)
                    this->commands[i].parameter.push_back(param[j]);
                this->commands[i].name = "arc";
                this->commands[i].converted = true;
            }
        }
    }
}
void _aff_file::arctap_skyline()
{
    for(int i = 0; i < this->commands.size(); i++)
    {
        if(!this->commands[i].converted)
        {
            if(this->commands[i].arctap.size() > 0)
            {
                for(int j = 0; j < this->commands[i].arctap.size(); j++)
                {
                    command tmp_cmd;
                    tmp_cmd.name = "arc";
                    tmp_cmd.parameter.push_back(this->commands[i].arctap[j]);
                    tmp_cmd.parameter.push_back(this->commands[i].arctap[j]);
                    double x = ( stod(this->commands[i].parameter[1]) - stod(this->commands[i].parameter[0]) ) *
                                ( stod(this->commands[i].parameter[3]) - stod(this->commands[i].parameter[2]) ) +
                                stod(this->commands[i].parameter[2]);
                    string str = to_string(x - 0.25);
                    if(x - 0.25 > 0)
                        str = str.substr(0, 4);
                    else
                        str = str.substr(0, 5);
                    tmp_cmd.parameter.push_back(str);
                    str = to_string(x + 0.25);
                    if(x + 0.25 > 0)
                        str = str.substr(0, 4);
                    else
                        str = str.substr(0, 5);
                    tmp_cmd.parameter.push_back(str);
                    tmp_cmd.parameter.push_back("s");

                    double y = ( stod(this->commands[i].parameter[1]) - stod(this->commands[i].parameter[0]) ) *\
                                ( stod(this->commands[i].parameter[6]) - stod(this->commands[i].parameter[5]) ) +\
                                stod(this->commands[i].parameter[5]);
                    str = to_string(y);
                    if(y > 0)
                        str = str.substr(0, 4);
                    else
                        str = str.substr(0, 5);
                    tmp_cmd.parameter.push_back(str);
                    tmp_cmd.parameter.push_back(str);

                    tmp_cmd.parameter.push_back("0");
                    tmp_cmd.parameter.push_back("none");
                    tmp_cmd.parameter.push_back("true");
                    tmp_cmd.converted = true;

                    this->commands[i].arctap.clear();
                    this->commands[i].converted = true;

                    i += 1;
                    this->commands.insert(this->commands.begin()+i, tmp_cmd);

                    //cout << "arctap_skyline() ing......" << this->commands[i].arctap.size() << "\t j= " << j << endl;
                }
                //cout<< "this->commands.size()=" << this->commands.size() << "\ti=" << i << endl;
            }

        }
    }
}


void _aff_file::remove_(string type)
{
    if(type == "arc")
    {
        for(int i = 0; i < commands.size(); i++)
        {
            if(commands[i].name == "arc")
                if(commands[i].parameter[9] == "false")
                    commands.erase(commands.begin() + i);
        }
    }
    else if(type == "skyline")
    {
        for(int i = 0; i < commands.size(); i++)
        {
            if(commands[i].name == "arc")
                if(commands[i].parameter[9] == "true")
                    commands.erase(commands.begin() + i);
        }
    }
    else if(type == "hold")
    {
        for(int i = 0; i < commands.size(); i++)
        {
            if(commands[i].name == "hold")
                commands.erase(commands.begin() + i);
        }
    }
    else if(type == "note")
    {
        for(int i = 0; i < commands.size(); i++)
        {
            if(commands[i].name == "tap")
                commands.erase(commands.begin() + i);
        }
    }
    else if(type == "arctap")
    {
        for(int i = 0; i < commands.size(); i++)
        {
            commands[i].arctap.clear();
        }
    }
    else
    {
        cout << "错误的输入！" << endl;
    }
}

void _aff_file::export_aff(string filename)
{
    ofstream outfile;
    outfile.open(filename.c_str(), std::ios::out/* | std::ios::app*/);
    if (!outfile.is_open())
        return;
    outfile << this->AudioOffset << endl;
    outfile << "-" << endl;
    outfile << this->Timing << endl;
    for(int i = 0; i < this->commands.size(); i++)
    {
        if(this->commands[i].name != "tap")
            outfile << this->commands[i].name;
        outfile << "(" << this->commands[i].parameter[0];
        for(int j = 1; j < this->commands[i].parameter.size(); j++)
            outfile << "," << this->commands[i].parameter[j];
        if(this->commands[i].arctap.size())
        {
            outfile << ")[arctap(" << this->commands[i].arctap[0];
            for(int j = 1; j < this->commands[i].arctap.size(); j++)
                outfile << "),arctap(" << this->commands[i].arctap[j];
            outfile << ")];" << endl;
        }
        else
        {
            outfile << ");" << endl;
        }
    }
    outfile.close();
}
