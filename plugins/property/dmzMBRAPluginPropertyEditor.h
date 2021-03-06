#ifndef DMZ_MBRA_PLUGIN_PROPERTY_EDITOR_DOT_H
#define DMZ_MBRA_PLUGIN_PROPERTY_EDITOR_DOT_H

#include <dmzRuntimeDataConverterTypesBase.h>
#include <dmzRuntimeDefinitions.h>
#include <dmzRuntimeLog.h>
#include <dmzRuntimeMessaging.h>
#include <dmzRuntimePlugin.h>
#include <dmzRuntimeUndo.h>
#include <dmzTypesStringSub.h>
#include <dmzTypesHashTableUInt32Template.h>

class QWidget;
class QFormLayout;

namespace dmz {

   class ObjectModule;
   class QtModuleMainWindow;

   class MBRAPluginPropertyEditor :
         public Plugin,
         public MessageObserver {

      public:
         class PropertyUpdater {

            public:
               const Handle AttrHandle;
               PropertyUpdater *next;

               virtual ~PropertyUpdater () {

                  while (next) {

                     PropertyUpdater *temp = next;
                     next = next->next;
                     temp->next = 0;
                     delete temp; temp = 0;
                  }
               }

               virtual QWidget *get_widget () = 0;

               virtual void update_object (const Handle Object, ObjectModule &module) = 0;

            protected:
               PropertyUpdater (const Handle TheAttrHandle) :
                     AttrHandle (TheAttrHandle),
                     next (0) {;}

            private:
               PropertyUpdater ();
               PropertyUpdater (const PropertyUpdater &);
               PropertyUpdater &operator= (const PropertyUpdater &);
         };

         class PropertyWidget {

            public:
               const Handle AttrHandle;
               const String Name;

               PropertyWidget *next;

               UInt32 tab;

               virtual ~PropertyWidget () {

                  while (next) {

                     PropertyWidget *temp = next;
                     next = next->next;
                     temp->next = 0;
                     delete temp; temp = 0;
                  }
               }

               virtual PropertyUpdater *create_widgets (
                  const Handle Object,
                  ObjectModule &module,
                  QWidget *parent,
                  QFormLayout *layout,
                  StringSub &sub) = 0;

            protected:
               PropertyWidget (
                     const Handle TheAttrHandle,
                     const String &TheName) :
                     AttrHandle (TheAttrHandle),
                     Name (TheName),
                     next (0),
                     tab (0) {;}

            private:
               PropertyWidget ();
               PropertyWidget (const PropertyWidget &);
               PropertyWidget &operator= (const PropertyWidget &);
         };

         MBRAPluginPropertyEditor (const PluginInfo &Info, Config &local);
         ~MBRAPluginPropertyEditor ();

         // Plugin Interface
         virtual void update_plugin_state (
            const PluginStateEnum State,
            const UInt32 Level);

         virtual void discover_plugin (
            const PluginDiscoverEnum Mode,
            const Plugin *PluginPtr);

         // Message Observer Interface
         virtual void receive_message (
            const Message &Type,
            const UInt32 MessageSendHandle,
            const Handle TargetObserverHandle,
            const Data *InData,
            Data *outData);

      protected:
         void _edit (const Handle Object, const Boolean Created);

         PropertyWidget *_create_widgets (Config &list);

         void _init (Config &local);

         Log _log;
         Undo _undo;
         Definitions _defs;

         HashTableUInt32Template<String> _tabNameTable;

         DataConverterString _convert;

         ObjectModule *_objMod;
         QtModuleMainWindow *_window;

         Boolean _showFTButton;

         Message _editMessage;
         Message _ftMessage;
         Message _unitsMessage;


         Handle _objectDataHandle;
         Handle _createdDataHandle;
         Handle _ftHandle;

         String _dialogTitle;

         StringSub _sub;

         PropertyWidget *_widgets;

      private:
         MBRAPluginPropertyEditor ();
         MBRAPluginPropertyEditor (const MBRAPluginPropertyEditor &);
         MBRAPluginPropertyEditor &operator= (const MBRAPluginPropertyEditor &);

   };
};

#endif // DMZ_MBRA_PLUGIN_PROPERTY_EDITOR_DOT_H
