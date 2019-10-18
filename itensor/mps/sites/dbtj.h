//
// Distributed under the ITensor Library License, Version 1.2
//    (See accompanying LICENSE file.)
//
#ifndef __ITENSOR_TJ_H
#define __ITENSOR_TJ_H
#include "itensor/mps/siteset.h"

namespace itensor {

class DBtJSite;

using DBtJ  = BasicSiteSet<DBtJSite>;

class DBtJSite
    {
    IQIndex s;
    public:

    DBtJSite() { }

    DBtJSite(IQIndex I) : s(I) { }

    DBtJSite(int n, Args const& args = Args::global())
        {
        s = IQIndex{nameint("DBtJ site=",n),
            Index(nameint("UpEmp ", n),1,Site),  QN("Sz=", +1,"Nf=",0),
            Index(nameint("DnEmp ", n),1,Site),  QN("Sz=", -1,"Nf=",0),
            Index(nameint("UpUp  ", n),1,Site),  QN("Sz=", +2,"Nf=",1),
            Index(nameint("DnDn  ", n),1,Site),  QN("Sz=", -2,"Nf=",1),
            Index(nameint("UpDn"  , n),1,Site),  QN("Sz=",  0,"Nf=",1),
            Index(nameint("DnUp  ", n),1,Site),  QN("Sz=",  0,"Nf=",1)};
        }

    IQIndex
    index() const { return s; }

    IQIndexVal
    state(std::string const& state)
        {
        if(state == "UpEmp") 
            {
            return s(1);
            }
        else 
        if(state == "DnEmp") 
            {
            return s(2);
            }
        else 
        if(state == "UpUp") 
            {
            return s(3);
            }
	if(state == "DnDn")
	    {
            return s(4);
	    }
	if(state == "UpDn")
	    {
            return s(5);
            }
	if(state == "DnUp")
	   {
           return s(6);
	   }
        else
            {
            Error("State " + state + " not recognized");
            }
        return IQIndexVal();
        }

	IQTensor
	op(std::string const& opname,
	   Args const& args) const
        {
        auto sP = prime(s);

        IQIndexVal UpEm(s(1)),
                   UpEmP(sP(1)),
                   DnEm(s(2)),
                   DnEmP(sP(2)),
		   UpUp(s(3)),
		   UpUpP(sP(3)),
		   DnDn(s(4)),
		   DnDnP(sP(4)),
                   UpDn(s(5)),
                   UpDnP(sP(5)),
	           DnUp(s(6)),
		   DnUpP(s(6));

        auto Op = IQTensor(dag(s),sP);

        if(opname == "Nup")
            {
            Op.set(UpUp,UpUpP,1);
            Op.set(DnUp,DnUpP,1);
            }
        else
        if(opname == "Ndn")
            {
            Op.set(DnDn,DnDnP,1);
	    Op.set(UpDn,UpDnP,1);
            }
        else
        if(opname == "Ntot")
            {
            Op.set(UpUp,UpUpP,1);
            Op.set(UpDn,UpDnP,1);
            Op.set(DnDn,DnDnP,1);
            Op.set(DnUp,DnUpP,1);
            }
        else
        if(opname == "Cup")
            {
            Op.set(UpUp,UpEmP,1); 
            Op.set(DnUp,DnEmP,1); 
            }
        else
        if(opname == "Cdagup")
            {
            Op.set(UpEm,UpUpP,1); 
            Op.set(DnEm,DnUpP,1); 
            }
        else
        if(opname == "Cdn")
            {
            Op.set(UpDn,UpEmP,1);
            Op.set(DnDn,DnEmP,1);
            }
        else
        if(opname == "Cdagdn")
            {
            Op.set(UpEm,UpDnP,1); 
            Op.set(DnEm,DnDnP,1); 
	    }  
        else
        if(opname == "Aup")
            {
            Op.set(UpUp,UpEmP,1); 
            Op.set(DnUp,DnEmP,1); 
            }
        else
        if(opname == "Adagup")
            {
            Op.set(UpEm,UpUpP,1); 
            Op.set(DnEm,DnUpP,1); 
            }
        else
        if(opname == "Adn")
            {
            Op.set(UpDn,UpEmP,1);
            Op.set(DnDn,DnEmP,1);
            }
        else
        if(opname == "Adagdn")
            {
            Op.set(UpEm,UpDnP,1); 
            Op.set(DnEm,DnDnP,1);
	    } 
        else
        if(opname == "FermiPhase" || opname == "F")
            {
            Op.set(UpEm,UpEmP,+1);
	    Op.set(DnEm,DnEmP,+1); 
            Op.set(UpUp,UpUpP,-1);
	    Op.set(DnUp,DnUpP,-1);
            Op.set(UpDn,UpDnP,-1);
	    Op.set(DnDn,DnDnP,-1);
            }
       // else
       // if(opname == "Fup")
       //     {
       //     Op.set(Em,EmP,+1); 
       //     Op.set(Up,UpP,-1);
       //     Op.set(Dn,DnP,+1);
       //     }
       // else
       // if(opname == "Fdn")
       //     {
       //     Op.set(Em,EmP,+1); 
       //     Op.set(Up,UpP,+1);
       //     Op.set(Dn,DnP,-1);
       //     }
       // else
       // if(opname == "LSz")
       //     {
       //     Op.set(UpUp,UpUpP,+0.5);
       //     Op.set(UpDn,UpDnP,+0.5);
       //     Op.set(UpDn,UpDnP,+0.5); 
       //     Op.set(Dn,DnP,-0.5);
       //     }
       // else
       // if(opname == "Sx")
       //     {
       //     Op.set(Up,DnP,1); 
       //     Op.set(Dn,UpP,1);
       //     }
       // else
       // if(opname == "Sp" || opname == "S+")
       //     {
       //     Op.set(Dn,UpP,1);
       //     }
       // else
       // if(opname == "Sm" || opname == "S-")
       //     {
       //     Op.set(Up,DnP,1);
       //     }
       // else
       //     {
       //     Error("Operator \"" + opname + "\" name not recognized");
       //     }

        return Op;
        }
    };

} //namespace itensor

#endif
