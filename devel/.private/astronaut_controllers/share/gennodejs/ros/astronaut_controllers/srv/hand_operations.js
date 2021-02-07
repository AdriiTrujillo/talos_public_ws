// Auto-generated. Do not edit!

// (in-package astronaut_controllers.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class hand_operationsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.operation = null;
      this.hand = null;
    }
    else {
      if (initObj.hasOwnProperty('operation')) {
        this.operation = initObj.operation
      }
      else {
        this.operation = '';
      }
      if (initObj.hasOwnProperty('hand')) {
        this.hand = initObj.hand
      }
      else {
        this.hand = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hand_operationsRequest
    // Serialize message field [operation]
    bufferOffset = _serializer.string(obj.operation, buffer, bufferOffset);
    // Serialize message field [hand]
    bufferOffset = _serializer.string(obj.hand, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hand_operationsRequest
    let len;
    let data = new hand_operationsRequest(null);
    // Deserialize message field [operation]
    data.operation = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [hand]
    data.hand = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.operation.length;
    length += object.hand.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'astronaut_controllers/hand_operationsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6dc96464fdf846c4cccabcfccb47a88f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string operation
    string hand
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hand_operationsRequest(null);
    if (msg.operation !== undefined) {
      resolved.operation = msg.operation;
    }
    else {
      resolved.operation = ''
    }

    if (msg.hand !== undefined) {
      resolved.hand = msg.hand;
    }
    else {
      resolved.hand = ''
    }

    return resolved;
    }
};

class hand_operationsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.succes = null;
    }
    else {
      if (initObj.hasOwnProperty('succes')) {
        this.succes = initObj.succes
      }
      else {
        this.succes = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hand_operationsResponse
    // Serialize message field [succes]
    bufferOffset = _serializer.bool(obj.succes, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hand_operationsResponse
    let len;
    let data = new hand_operationsResponse(null);
    // Deserialize message field [succes]
    data.succes = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'astronaut_controllers/hand_operationsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '509793171e494962cd366ecf60e100e4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    bool succes
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hand_operationsResponse(null);
    if (msg.succes !== undefined) {
      resolved.succes = msg.succes;
    }
    else {
      resolved.succes = false
    }

    return resolved;
    }
};

module.exports = {
  Request: hand_operationsRequest,
  Response: hand_operationsResponse,
  md5sum() { return 'e64cddebc1c701e9b45008b7ec9f9d6d'; },
  datatype() { return 'astronaut_controllers/hand_operations'; }
};
