#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<utility>

using namespace std;

int main()
{
    ifstream input;
    string in_name = "";
    cout<<"input a file"<<endl;
    cin>>in_name;
    input.open(in_name);
    if(!input.is_open())
    {
        cout<<"No such file!"<<endl;
        return 0;
    }
    
    double xbsize,ybsize=0;
    cout<<"input xbin size, ybin size:"<<endl;
    cin>>xbsize>>ybsize;
    
    double xmax,xmin,ymax,ymin =0;
    cout<<"input xmin,xmax,ymin,ymax"<<endl;
    cin>>xmin>>xmax>>ymin>>ymax;
    
    int xbnum = 1+(xmax-xmin)/xbsize;
    int ybnum = 1+(ymax-ymin)/ybsize;
    
    double** PMF = new double* [xbnum];
    for(int i=0;i<xbnum;i++)
    {
        PMF[i] = new double[ybnum];
    }
   
    string skip="";
    getline(input,skip);
    
    for(int i=0;i<xbnum;i++)
    {
        for(int j=0;j<ybnum;j++)
        {
            input>>skip>>skip>>PMF[i][j]>>skip;
            //cout<<PMF[i][j]<<endl;
        }
    }
    
    double x_st,y_st=0;
    cout<<"starting point:"<<endl;
    cin>>x_st>>y_st;
    int x_index = (x_st-xmin)/xbsize;
    int y_index = (y_st-ymin)/ybsize;
    double PMF_st = PMF[x_index][y_index];
    ofstream output(in_name+"result.txt");
    vector<pair<int,int>> x_y;
    x_y.push_back(make_pair(x_index,y_index));
    cout<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_st<<endl;
    output<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_st<<endl;
    
    double neighbor_up = PMF[x_index][y_index];
    double neighbor_down = PMF[x_index][y_index];
    double neighbor_right = PMF[x_index][y_index];
    //double PMF_next = PMF[x_index][y_index];
    
    while(x_index<=xbnum-1 && x_index>=0 && y_index<=ybnum-1 && y_index>=0)
    {
        if(y_index<ybnum-1)
        neighbor_up = PMF[x_index][y_index+1];
        
        
        if(y_index>0)
        neighbor_down = PMF[x_index][y_index-1];
    
        
        if(x_index<xbnum-1)
        neighbor_right = PMF[x_index+1][y_index];
        else
        break;
            
        double PMF_old =PMF[x_index][y_index];
        double PMF_next = PMF[x_index][y_index];
        
        if(neighbor_up<=neighbor_down && neighbor_up<=neighbor_right /*&& neighbor_up<=PMF_old*/)
        {
            
            y_index++;
            if(x_y.size()>2)
            {
                if(y_index==x_y[x_y.size()-2].second && x_index == x_y[x_y.size()-2].first) //prevent stepping back and forth
                {
                    y_index--;
                    if(neighbor_right<=neighbor_down)
                    {
                        PMF_next = neighbor_right;
                        x_index++;
                    }
                    else
                    {
                        PMF_next = neighbor_down;
                        y_index--;
                    }
                    if(PMF_next==PMF_old)
                    {
                        cout<<"done"<<endl;
                        break;
                    }
                    x_y.push_back(make_pair(x_index,y_index));
                    cout<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_next<<endl;
                    output<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_next<<endl;
                    continue;
                }
            }
            PMF_next = neighbor_up;
            
        }
        if(neighbor_down<=neighbor_up && neighbor_down<=neighbor_right /*&& neighbor_down<=PMF_old*/)
        {
            y_index--;
            
            if(x_y.size()>2)
            {
                if(y_index==x_y[x_y.size()-2].second && x_index == x_y[x_y.size()-2].first) //prevent stepping back and forth
                {
                    y_index++;
                    if(neighbor_right<=neighbor_up)
                    {
                        PMF_next = neighbor_right;
                        x_index++;
                    }
                    else
                    {
                        PMF_next = neighbor_up;
                        y_index++;
                    }
                    if(PMF_next==PMF_old)
                    {
                        cout<<"done"<<endl;
                        break;
                    }
                    x_y.push_back(make_pair(x_index,y_index));
                    cout<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_next<<endl;
                    output<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_next<<endl;
                    continue;
                }
            }
            PMF_next = neighbor_down;
        }
        if(neighbor_right<=neighbor_up && neighbor_right<=neighbor_down /*&& neighbor_right<=PMF_old*/)
        {
            x_index++;
            PMF_next = neighbor_right;
        }
        if(PMF_next==PMF_old)
        {
            cout<<"done"<<endl;
            break;
        }
        x_y.push_back(make_pair(x_index,y_index));
        cout<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_next<<endl;
        output<<xmin+x_index*xbsize<<" "<<ymin+y_index*ybsize<<" "<<PMF_next<<endl;
    }
}















