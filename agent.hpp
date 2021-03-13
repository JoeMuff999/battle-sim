#include "point.hpp"
#include "drawable.hpp"
#include <string>
#include <stdio.h>
#include <unistd.h>
/*
    base class from which all other agents inherit their functions
*/
class Agent : public Drawable {
    Point _point;
    public:
        const std::string getImgPath()
        {
            string dummy;
            return dummy;   
        }
        Point getPos(){
            return _point;
        }
        void setPos(Point point){
            _point = point; 
        }
        //A*
        void pathToPoint()
        {
            
        }
};

class FriendlyAgent : public Agent{
    string bmp_path = "/sprites/agent.bmp";
    const std::string getImgPath()
    {
        char cwd[FILENAME_MAX];
        getcwd(cwd, FILENAME_MAX);
        
        std::string currDir(cwd);
        currDir += bmp_path;
        // cout << "in img path " << currDir <<  " size = " << currDir.size() <<endl;
        
        return currDir;
    }
};