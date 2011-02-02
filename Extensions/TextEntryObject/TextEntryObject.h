/**

Game Develop - TextEntry Object Extension
Copyright (c) 2011 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "GDL/Object.h"
#include <SFML/Graphics.hpp>
class Evaluateur;
class ImageManager;
class RuntimeScene;
class Object;
class ExpressionInstruction;
class ObjectsConcerned;
class ImageManager;
class InitialPosition;
#if defined(GD_IDE_ONLY)
class wxBitmap;
class Game;
class wxWindow;
class MainEditorCommand;
class ResourcesMergingHelper;
#endif

/**
 * TextEntry Object
 */
class TextEntryObject : public Object
{
    public :

        TextEntryObject(std::string name_);
        virtual ~TextEntryObject() {};
        virtual ObjSPtr Clone() { return boost::shared_ptr<Object>(new TextEntryObject(*this));}

        virtual bool LoadRuntimeResources(const RuntimeScene & scene, const ImageManager & imageMgr );
        virtual bool InitializeFromInitialPosition(const InitialPosition & position);

        virtual bool Draw(sf::RenderWindow& main_window);

        virtual void UpdateTime(float);

        #if defined(GD_IDE_ONLY)
        virtual bool DrawEdittime(sf::RenderWindow& main_window);
        virtual void PrepareResourcesForMerging(ResourcesMergingHelper & resourcesMergingHelper);
        virtual bool GenerateThumbnail(const Game & game, wxBitmap & thumbnail);

        virtual void EditObject( wxWindow* parent, Game & game_, MainEditorCommand & mainEditorCommand_ );
        virtual wxPanel * CreateInitialPositionPanel( wxWindow* parent, const Game & game_, const Scene & scene_, const InitialPosition & position );
        virtual void UpdateInitialPositionFromPanel(wxPanel * panel, InitialPosition & position);

        virtual void GetPropertyForDebugger (unsigned int propertyNb, string & name, string & value) const;
        virtual bool ChangeProperty(unsigned int propertyNb, string newValue);
        virtual unsigned int GetNumberOfProperties() const;
        #endif

        virtual void LoadFromXml(const TiXmlElement * elemScene);
        #if defined(GD_IDE_ONLY)
        virtual void SaveToXml(TiXmlElement * elemScene);
        #endif

        virtual float GetWidth() const;
        virtual float GetHeight() const;

        virtual float GetDrawableX() const;
        virtual float GetDrawableY() const;

        virtual float GetCenterX() const;
        virtual float GetCenterY() const;

        inline void SetString(std::string str) { text = str; };
        inline std::string GetString() const { return text;};

        //ACE for string
        bool CondString( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition );
        bool ActString( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action );
        std::string ExpString( const RuntimeScene & scene, ObjectsConcerned & objectsConcerned, ObjSPtr obj1, ObjSPtr obj2, const StrExpressionInstruction & exprInstruction );

        //ACE for font and size
        bool ActActivate( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action );
        bool CondActivated( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition );

    private:

        std::string text;
        const std::string * sceneTextEntered; ///< Pointer to the input received by the scene. Initialized during LoadRuntimeResources call.
        bool activated;
};

void DestroyTextEntryObject(Object * object);
Object * CreateTextEntryObject(std::string name);

#endif // TEXTOBJECT_H
