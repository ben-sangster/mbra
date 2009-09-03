local NodeType = dmz.object_type.new ("na_node")

function receive_select (self, type, data)
   self.firstMove = true
   if dmz.data.is_a (data) then
      self.handle = data:lookup_handle ("object", 1)
      local pos = data:lookup_vector ("position", 1)
      if self.handle and pos then
         local ObjType = dmz.object.type (self.handle)
         if ObjType and ObjType:is_of_type (NodeType) then
            local cpos = dmz.object.position (self.handle)
            if cpos then self.offset = cpos - pos
            else self.offset = dmz.vector.new ()
            end
         else self.handle = nil
         end
      end
   end
end

function receive_unselect (self, type, data)
   self.handle = nil
   self.offset = nil
end

function receive_move (self, type, data)
   if self.handle and dmz.data.is_a (data) then
      local undoHandle = nil
      if self.firstMove then
         undoHandle = dmz.undo.start_record ("Move Node")
         self.firstMove = false
      end
      local pos = data:lookup_vector ("position", 1)
      if self.handle and pos then
         dmz.object.position (self.handle, nil, pos + self.offset)
      end
      if undoHandle then dmz.undo.stop_record (undoHandle) end
   end
end

function new (config, name)
   local self = {
      log = dmz.log.new ("lua." .. name),
      selectMessage =
         config:to_message ("message.select.name", "SelectMoveObjectMessage"),
      unselectMessage =
         config:to_message (
            "message.unselect.name",
            "UnselectMoveObjectMessage"),
      moveMessage =
         config:to_message ("message.move.name", "MoveSelectedObjectMessage"),
      obs = dmz.message_observer.new (name),
   }

   self.log:info ("Creating plugin: " .. name)
   self.obs:register (self.selectMessage, receive_select, self)
   self.obs:register (self.unselectMessage, receive_unselect, self)
   self.obs:register (self.moveMessage, receive_move, self)

   return self
end
