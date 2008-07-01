#ifndef DMZ_MBRA_PLUGIN_FAULT_TREE_AUTO_LAYOUT_DOT_H
#define DMZ_MBRA_PLUGIN_FAULT_TREE_AUTO_LAYOUT_DOT_H

#include <dmzObjectObserverUtil.h>
#include <dmzRuntimeLog.h>
#include <dmzRuntimeObjectType.h>
#include <dmzRuntimePlugin.h>
#include <dmzRuntimeTimeSlice.h>
#include <dmzTypesHandleContainer.h>
#include <dmzTypesHashTableHandleTemplate.h>
#include <dmzTypesVector.h>
#include <QtGui/QGraphicsPathItem>
#include <QtGui/QPainterPath>

namespace dmz {

   class QtModuleCanvas;


   class MBRAPluginFaultTreeAutoLayout :
         public Plugin,
         public TimeSlice,
         public ObjectObserverUtil {

      public:
         MBRAPluginFaultTreeAutoLayout (const PluginInfo &Info, Config &local);
         ~MBRAPluginFaultTreeAutoLayout ();

         // Plugin Interface
         virtual void update_plugin_state (
            const PluginStateEnum State,
            const UInt32 Level) {;}

         virtual void discover_plugin (
            const PluginDiscoverEnum Mode,
            const Plugin *PluginPtr);

         // TimeSlice Interface
         virtual void update_time_slice (const Float64 TimeDelta);

         // Object Observer Interface
         virtual void create_object (
            const UUID &Identity,
            const Handle ObjectHandle,
            const ObjectType &Type,
            const ObjectLocalityEnum Locality);

         virtual void destroy_object (const UUID &Identity, const Handle ObjectHandle);

         virtual void link_objects (
            const Handle LinkHandle,
            const Handle AttributeHandle,
            const UUID &SuperIdentity,
            const Handle SuperHandle,
            const UUID &SubIdentity,
            const Handle SubHandle);

         virtual void unlink_objects (
            const Handle LinkHandle,
            const Handle AttributeHandle,
            const UUID &SuperIdentity,
            const Handle SuperHandle,
            const UUID &SubIdentity,
            const Handle SubHandle);

      protected:
         void _update_tree ();

         void _update_tree (
            const Handle SuperHandle,
            const Handle SubHandle,
            const Int32 Column,
            Int32 &count);

         void _update_logic (const Handle Parent);

         void _update_path (const Handle Object);

         Handle _create_root ();

         void _init (Config &local);

         Log _log;
         QtModuleCanvas *_canvasModule;
         String _canvasModuleName;
         Handle _defaultAttrHandle;
         Handle _linkAttrHandle;
         Handle _logicAttrHandle;
         Handle _nameAttrHandle;
         Handle _root;
         Handle _subHandle;
         ObjectType _rootType;
         String _rootText;
         Float64 _hOffset;
         Float64 _vOffset;
         Boolean _doTreeUpdate;
         Boolean _doZoomUpdate;
         QPainterPath _path;
         QGraphicsPathItem *_pathItem;

      private:
         MBRAPluginFaultTreeAutoLayout ();
         MBRAPluginFaultTreeAutoLayout (const MBRAPluginFaultTreeAutoLayout &);
         MBRAPluginFaultTreeAutoLayout &operator= (const MBRAPluginFaultTreeAutoLayout &);
   };
};

#endif // DMZ_MBRA_PLUGIN_FAULT_TREE_AUTO_LAYOUT_DOT_H
