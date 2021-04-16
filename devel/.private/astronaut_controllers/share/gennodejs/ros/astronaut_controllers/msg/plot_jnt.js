// Auto-generated. Do not edit!

// (in-package astronaut_controllers.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class plot_jnt {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.jnt_0 = null;
      this.jnt_1 = null;
      this.jnt_2 = null;
      this.jnt_3 = null;
      this.jnt_4 = null;
      this.jnt_5 = null;
      this.jnt_6 = null;
    }
    else {
      if (initObj.hasOwnProperty('jnt_0')) {
        this.jnt_0 = initObj.jnt_0
      }
      else {
        this.jnt_0 = 0.0;
      }
      if (initObj.hasOwnProperty('jnt_1')) {
        this.jnt_1 = initObj.jnt_1
      }
      else {
        this.jnt_1 = 0.0;
      }
      if (initObj.hasOwnProperty('jnt_2')) {
        this.jnt_2 = initObj.jnt_2
      }
      else {
        this.jnt_2 = 0.0;
      }
      if (initObj.hasOwnProperty('jnt_3')) {
        this.jnt_3 = initObj.jnt_3
      }
      else {
        this.jnt_3 = 0.0;
      }
      if (initObj.hasOwnProperty('jnt_4')) {
        this.jnt_4 = initObj.jnt_4
      }
      else {
        this.jnt_4 = 0.0;
      }
      if (initObj.hasOwnProperty('jnt_5')) {
        this.jnt_5 = initObj.jnt_5
      }
      else {
        this.jnt_5 = 0.0;
      }
      if (initObj.hasOwnProperty('jnt_6')) {
        this.jnt_6 = initObj.jnt_6
      }
      else {
        this.jnt_6 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type plot_jnt
    // Serialize message field [jnt_0]
    bufferOffset = _serializer.float64(obj.jnt_0, buffer, bufferOffset);
    // Serialize message field [jnt_1]
    bufferOffset = _serializer.float64(obj.jnt_1, buffer, bufferOffset);
    // Serialize message field [jnt_2]
    bufferOffset = _serializer.float64(obj.jnt_2, buffer, bufferOffset);
    // Serialize message field [jnt_3]
    bufferOffset = _serializer.float64(obj.jnt_3, buffer, bufferOffset);
    // Serialize message field [jnt_4]
    bufferOffset = _serializer.float64(obj.jnt_4, buffer, bufferOffset);
    // Serialize message field [jnt_5]
    bufferOffset = _serializer.float64(obj.jnt_5, buffer, bufferOffset);
    // Serialize message field [jnt_6]
    bufferOffset = _serializer.float64(obj.jnt_6, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type plot_jnt
    let len;
    let data = new plot_jnt(null);
    // Deserialize message field [jnt_0]
    data.jnt_0 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [jnt_1]
    data.jnt_1 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [jnt_2]
    data.jnt_2 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [jnt_3]
    data.jnt_3 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [jnt_4]
    data.jnt_4 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [jnt_5]
    data.jnt_5 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [jnt_6]
    data.jnt_6 = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 56;
  }

  static datatype() {
    // Returns string type for a message object
    return 'astronaut_controllers/plot_jnt';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3b09b9904d6a381558d8c771bafb8d82';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 jnt_0
    float64 jnt_1
    float64 jnt_2
    float64 jnt_3
    float64 jnt_4
    float64 jnt_5
    float64 jnt_6
    
    
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new plot_jnt(null);
    if (msg.jnt_0 !== undefined) {
      resolved.jnt_0 = msg.jnt_0;
    }
    else {
      resolved.jnt_0 = 0.0
    }

    if (msg.jnt_1 !== undefined) {
      resolved.jnt_1 = msg.jnt_1;
    }
    else {
      resolved.jnt_1 = 0.0
    }

    if (msg.jnt_2 !== undefined) {
      resolved.jnt_2 = msg.jnt_2;
    }
    else {
      resolved.jnt_2 = 0.0
    }

    if (msg.jnt_3 !== undefined) {
      resolved.jnt_3 = msg.jnt_3;
    }
    else {
      resolved.jnt_3 = 0.0
    }

    if (msg.jnt_4 !== undefined) {
      resolved.jnt_4 = msg.jnt_4;
    }
    else {
      resolved.jnt_4 = 0.0
    }

    if (msg.jnt_5 !== undefined) {
      resolved.jnt_5 = msg.jnt_5;
    }
    else {
      resolved.jnt_5 = 0.0
    }

    if (msg.jnt_6 !== undefined) {
      resolved.jnt_6 = msg.jnt_6;
    }
    else {
      resolved.jnt_6 = 0.0
    }

    return resolved;
    }
};

module.exports = plot_jnt;
