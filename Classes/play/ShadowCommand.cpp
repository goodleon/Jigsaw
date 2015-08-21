//
//  ShadowCommand.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-8-20.
//
//

#include "ShadowCommand.h"
#include "cex.h"
#include "stringex.h"
#include <stdlib.h>

struct TempShadowCommand
{
    string file;
    string command;
};

std::map<string, TempShadowCommand> getCommand()
{
    std::map<string, TempShadowCommand> ret;
    ret["VVVV"] = TempShadowCommand{"sdpng/sds-vvvv.png", ""};
    ret["VVVF"] = TempShadowCommand{"sdpng/sds-vvvf.png", ""};
    ret["VVVA"] = TempShadowCommand{"sdpng/sds-vvva.png", ""};
    ret["VVFV"] = TempShadowCommand{"sdpng/sds-vvvf.png", "rot=270"};
    ret["VVFF"] = TempShadowCommand{"sdpng/sds-vvff.png", ""};
    ret["VVFA"] = TempShadowCommand{"sdpng/sds-vvfa.png", ""};
    ret["VVAV"] = TempShadowCommand{"sdpng/sds-vvva.png", "rot=270"};
    ret["VVAF"] = TempShadowCommand{"sdpng/sds-vvfa.png", "flipX;rot=90"};
    ret["VVAA"] = TempShadowCommand{"sdpng/sds-vvaa.png", ""};
    ret["VFVV"] = TempShadowCommand{"sdpng/sds-vvvf.png", "rot=180"};
    ret["VFVA"] = TempShadowCommand{"sdpng/sds-vfva.png", ""};
    ret["VFFV"] = TempShadowCommand{"sdpng/sds-vvff.png", "rot=270"};
    ret["VFFA"] = TempShadowCommand{"sdpng/sds-vffa.png", ""};
    ret["VFAV"] = TempShadowCommand{"sdpng/sds-vvfa.png", "rot=270"};
    ret["VAVV"] = TempShadowCommand{"sdpng/sds-vvav.png", "rot=270"};
    ret["VAVA"] = TempShadowCommand{"sdpng/sds-vava.png", ""};
    ret["VAFA"] = TempShadowCommand{"sdpng/sds-vafa.png", ""};
    ret["VAAA"] = TempShadowCommand{"sdpng/sds-vaaa.png", ""};
    ret["FVVV"] = TempShadowCommand{"sdpng/sds-vvvf.png", "rot=90"};
    ret["FVVF"] = TempShadowCommand{"sdpng/sds-vvff.png", "rot=90"};
    ret["FFVV"] = TempShadowCommand{"sdpng/sds-vvff.png", "rot=180"};
    ret["FFAV"] = TempShadowCommand{"sdpng/sds-vffa.png", "rot=270"};
    ret["FAVV"] = TempShadowCommand{"sdpng/sds-vfav.png", "rot=270"};
    ret["FAVF"] = TempShadowCommand{"sdpng/sds-vffa.png", "rot=180"};
    ret["FAVA"] = TempShadowCommand{"sdpng/sds-vafa.png", "rot=180"};
    ret["AVVV"] = TempShadowCommand{"sdpng/sds-vvav.png", "rot=180"};
    ret["AVVF"] = TempShadowCommand{"sdpng/sds-vfav.png", "rot=180"};
    ret["AVFF"] = TempShadowCommand{"sdpng/sds-vffa.png", "rot=90"};
    ret["AVAV"] = TempShadowCommand{"sdpng/sds-vava.png", "rot=90"};
    ret["AVAF"] = TempShadowCommand{"sdpng/sds-vafa.png", "rot=90"};
    ret["AVAA"] = TempShadowCommand{"sdpng/sds-vaaa.png", "rot=90"};
    ret["AFAV"] = TempShadowCommand{"sdpng/sds-vafa.png", "rot=270"};
    ret["AAVA"] = TempShadowCommand{"sdpng/sds-vaaa.png", "rot=180"};
    ret["AAAV"] = TempShadowCommand{"sdpng/sds-vaaa.png", "rot=270"};
    ret["AAAA"] = TempShadowCommand{"sdpng/sds-aaaa.png", ""};
    ret["AAAF"] = TempShadowCommand{"sdpng/sds-aaaf.png", ""};
    ret["AAFA"] = TempShadowCommand{"sdpng/sds-aaaf.png", "rot=270"};
    ret["AFAA"] = TempShadowCommand{"sdpng/sds-aaaf.png", "rot=180"};
    ret["FAAA"] = TempShadowCommand{"sdpng/sds-aaaf.png", "rot=90"};
    ret["VFAA"] = TempShadowCommand{"sdpng/sds-vfaa.png", ""};
    ret["VAVF"] = TempShadowCommand{"sdpng/sds-vfva.png", "flipX"};
    ret["VAFV"] = TempShadowCommand{"sdpng/sds-vvfa.png", "flipX"};
    ret["VAFF"] = TempShadowCommand{"sdpng/sds-vffa.png", "flipX"};
    ret["VAAV"] = TempShadowCommand{"sdpng/sds-vvaa.png", "flipX"};
    ret["VAAF"] = TempShadowCommand{"sdpng/sds-vfaa.png", "flipX"};
    ret["FVVA"] = TempShadowCommand{"sdpng/sds-vvfa.png", "flipY"};
    ret["FVAV"] = TempShadowCommand{"sdpng/sds-vfva.png", "rot=270"};
    ret["FVAF"] = TempShadowCommand{"sdpng/sds-vffa.png", "flipX;rot=90"};
    ret["FVAA"] = TempShadowCommand{"sdpng/sds-vfaa.png", "flipX;rot=90"};
    ret["FFVA"] = TempShadowCommand{"sdpng/sds-vffa.png", "flipX;rot=180"};
    ret["FAAV"] = TempShadowCommand{"sdpng/sds-vfaa.png", "rot=270"};
    ret["AVVA"] = TempShadowCommand{"sdpng/sds-vvaa.png", "rot=90"};
    ret["AVFV"] = TempShadowCommand{"sdpng/sds-vfva.png", "rot=90"};
    ret["AVFA"] = TempShadowCommand{"sdpng/sds-vfaa.png", "rot=90"};
    ret["AFVV"] = TempShadowCommand{"sdpng/sds-vfav.png", "flipX;rot=180;"};
    ret["AFVA"] = TempShadowCommand{"sdpng/sds-vfaa.png", "flipX;rot=180"};
    ret["AFFV"] = TempShadowCommand{"sdpng/sds-vffa.png", "flipX;rot=270"};
    ret["AAVV"] = TempShadowCommand{"sdpng/sds-vvaa.png", "rot=180"};
    ret["AAVF"] = TempShadowCommand{"sdpng/sds-vfaa.png", "rot=180"};
    ret["AAFV"] = TempShadowCommand{"sdpng/sds-vfaa.png", "flipX;rot=270"};
    ret["FAAF"] = TempShadowCommand{"sdpng/sds-faaf.png", ""};
    ret["FFAA"] = TempShadowCommand{"sdpng/sds-faaf.png", "rot=90"};
    ret["AFFA"] = TempShadowCommand{"sdpng/sds-faaf.png", "rot=180"};
    ret["AAFF"] = TempShadowCommand{"sdpng/sds-faaf.png", "rot=270"};
    return ret;
}

string getFormatEdges(const std::vector<EdgeType>& edges)
{
    string ret;
    for (EdgeType type : edges)
    {
        if (type==ET_A){
            ret.push_back('A');
        }
        else if (type==ET_V){
            ret.push_back('V');
        }
        else if (type==ET_F){
            ret.push_back('F');
        }
    }
    return ret;
}

void configShadowBySingleCommand(Sprite* shadow, const vector<string>& cmd)
{
    if (cmd.at(0) == "flipX")
    {
        shadow->setFlippedX(true);
    }
    else if (cmd.at(0) == "flipY")
    {
        shadow->setFlippedY(true);
    }
    else if (cmd.at(0) == "rot")
    {
        float angle = atof( cmd.at(1).c_str() );
        shadow->setRotation(angle);
    }
}
void configShadowByCommand(Sprite* shadow, const string& cmd)
{
    vector<string> command = cex::split(cmd, ';');
    for (string& one: command)
    {
        configShadowBySingleCommand(shadow, cex::split(one, '='));
    }
}

Sprite* ShadowCommand::createShadowByEdges(const std::vector<EdgeType>& edges)
{
    static std::map<string, TempShadowCommand> cmd = getCommand();
    string format = getFormatEdges(edges);
    auto target = cmd.find(format);
    CCASSERT(target != cmd.end(), "");
    
    Sprite* ret = Sprite::create( target->second.file );
    configShadowByCommand(ret, target->second.command);
    return ret;
}




