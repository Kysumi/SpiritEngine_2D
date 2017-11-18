//
//  LuaBoxShape.hpp
//  SEMAC
//
//  Created by Scott Maunder on 24/03/17.
//  Copyright © 2017 Scott Maunder. All rights reserved.
//

#ifndef LUABOXSHAPE_H
#define LUABOXSHAPE_H

#include "BaseModule.h"
#include "BoxShape.h"

namespace le {
    
    class LuaBoxShape : public BaseModule
    {
    public:
        
        // Inherited via BaseModule
        virtual void RegisterFunctions(LuaScript * L) override;
        virtual void RegisterFunctions(lua_State * L) override;
        
        static int resetPosition(lua_State *L);
        static int setPosition(lua_State *L);
        static int setSize(lua_State *L);
        static int setWorld(lua_State *L);
        static int getPosition(lua_State *L);
        static int setColor(lua_State *L);
        
    private:
        
    };
}



#endif /* LuaBoxShape_hpp */
