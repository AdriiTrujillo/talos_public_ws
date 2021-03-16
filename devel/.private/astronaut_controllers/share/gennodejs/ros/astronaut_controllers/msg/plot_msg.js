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

class plot_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x_err = null;
      this.y_err = null;
      this.z_err = null;
      this.roll_err = null;
      this.pitch_err = null;
      this.yaw_err = null;
    }
    else {
      if (initObj.hasOwnProperty('x_err')) {
        this.x_err = initObj.x_err
      }
      else {
        this.x_err = 0.0;
      }
      if (initObj.hasOwnProperty('y_err')) {
        this.y_err = initObj.y_err
      }
      else {
        this.y_err = 0.0;
      }
      if (initObj.hasOwnProperty('z_err')) {
        this.z_err = initObj.z_err
      }
      else {
        this.z_err = 0.0;
      }
      if (initObj.hasOwnProperty('roll_err')) {
        this.roll_err = initObj.roll_err
      }
      else {
        this.roll_err = 0.0;
      }
      if (initObj.hasOwnProperty('pitch_err')) {
        this.pitch_err = initObj.pitch_err
      }
      else {
        this.pitch_err = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_err')) {
        this.yaw_err = initObj.yaw_err
      }
      else {
        this.yaw_err = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type plot_msg
    // Serialize message field [x_err]
    bufferOffset = _serializer.float64(obj.x_err, buffer, bufferOffset);
    // Serialize message field [y_err]
    bufferOffset = _serializer.float64(obj.y_err, buffer, bufferOffset);
    // Serialize message field [z_err]
    bufferOffset = _serializer.float64(obj.z_err, buffer, bufferOffset);
    // Serialize message field [roll_err]
    bufferOffset = _serializer.float64(obj.roll_err, buffer, bufferOffset);
    // Serialize message field [pitch_err]
    bufferOffset = _serializer.float64(obj.pitch_err, buffer, bufferOffset);
    // Serialize message field [yaw_err]
    bufferOffset = _serializer.float64(obj.yaw_err, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type plot_msg
    let len;
    let data = new plot_msg(null);
    // Deserialize message field [x_err]
    data.x_err = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y_err]
    data.y_err = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [z_err]
    data.z_err = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [roll_err]
    data.roll_err = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [pitch_err]
    data.pitch_err = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [yaw_err]
    data.yaw_err = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 48;
  }

  static datatype() {
    // Returns string type for a message object
    return 'astronaut_controllers/plot_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2e3b1b0cf6c1e9ca2b791e3388980632';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 x_err
    float64 y_err
    float64 z_err
    float64 roll_err
    float64 pitch_err
    float64 yaw_err
    
    
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new plot_msg(null);
    if (msg.x_err !== undefined) {
      resolved.x_err = msg.x_err;
    }
    else {
      resolved.x_err = 0.0
    }

    if (msg.y_err !== undefined) {
      resolved.y_err = msg.y_err;
    }
    else {
      resolved.y_err = 0.0
    }

    if (msg.z_err !== undefined) {
      resolved.z_err = msg.z_err;
    }
    else {
      resolved.z_err = 0.0
    }

    if (msg.roll_err !== undefined) {
      resolved.roll_err = msg.roll_err;
    }
    else {
      resolved.roll_err = 0.0
    }

    if (msg.pitch_err !== undefined) {
      resolved.pitch_err = msg.pitch_err;
    }
    else {
      resolved.pitch_err = 0.0
    }

    if (msg.yaw_err !== undefined) {
      resolved.yaw_err = msg.yaw_err;
    }
    else {
      resolved.yaw_err = 0.0
    }

    return resolved;
    }
};

module.exports = plot_msg;
