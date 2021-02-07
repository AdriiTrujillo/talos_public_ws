; Auto-generated. Do not edit!


(cl:in-package astronaut_controllers-srv)


;//! \htmlinclude hand_operations-request.msg.html

(cl:defclass <hand_operations-request> (roslisp-msg-protocol:ros-message)
  ((operation
    :reader operation
    :initarg :operation
    :type cl:string
    :initform "")
   (hand
    :reader hand
    :initarg :hand
    :type cl:string
    :initform ""))
)

(cl:defclass hand_operations-request (<hand_operations-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hand_operations-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hand_operations-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name astronaut_controllers-srv:<hand_operations-request> is deprecated: use astronaut_controllers-srv:hand_operations-request instead.")))

(cl:ensure-generic-function 'operation-val :lambda-list '(m))
(cl:defmethod operation-val ((m <hand_operations-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-srv:operation-val is deprecated.  Use astronaut_controllers-srv:operation instead.")
  (operation m))

(cl:ensure-generic-function 'hand-val :lambda-list '(m))
(cl:defmethod hand-val ((m <hand_operations-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-srv:hand-val is deprecated.  Use astronaut_controllers-srv:hand instead.")
  (hand m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hand_operations-request>) ostream)
  "Serializes a message object of type '<hand_operations-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'operation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'operation))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'hand))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'hand))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hand_operations-request>) istream)
  "Deserializes a message object of type '<hand_operations-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'operation) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'operation) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'hand) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'hand) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hand_operations-request>)))
  "Returns string type for a service object of type '<hand_operations-request>"
  "astronaut_controllers/hand_operationsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hand_operations-request)))
  "Returns string type for a service object of type 'hand_operations-request"
  "astronaut_controllers/hand_operationsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hand_operations-request>)))
  "Returns md5sum for a message object of type '<hand_operations-request>"
  "e64cddebc1c701e9b45008b7ec9f9d6d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hand_operations-request)))
  "Returns md5sum for a message object of type 'hand_operations-request"
  "e64cddebc1c701e9b45008b7ec9f9d6d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hand_operations-request>)))
  "Returns full string definition for message of type '<hand_operations-request>"
  (cl:format cl:nil "string operation~%string hand~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hand_operations-request)))
  "Returns full string definition for message of type 'hand_operations-request"
  (cl:format cl:nil "string operation~%string hand~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hand_operations-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'operation))
     4 (cl:length (cl:slot-value msg 'hand))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hand_operations-request>))
  "Converts a ROS message object to a list"
  (cl:list 'hand_operations-request
    (cl:cons ':operation (operation msg))
    (cl:cons ':hand (hand msg))
))
;//! \htmlinclude hand_operations-response.msg.html

(cl:defclass <hand_operations-response> (roslisp-msg-protocol:ros-message)
  ((succes
    :reader succes
    :initarg :succes
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass hand_operations-response (<hand_operations-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hand_operations-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hand_operations-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name astronaut_controllers-srv:<hand_operations-response> is deprecated: use astronaut_controllers-srv:hand_operations-response instead.")))

(cl:ensure-generic-function 'succes-val :lambda-list '(m))
(cl:defmethod succes-val ((m <hand_operations-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-srv:succes-val is deprecated.  Use astronaut_controllers-srv:succes instead.")
  (succes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hand_operations-response>) ostream)
  "Serializes a message object of type '<hand_operations-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'succes) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hand_operations-response>) istream)
  "Deserializes a message object of type '<hand_operations-response>"
    (cl:setf (cl:slot-value msg 'succes) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hand_operations-response>)))
  "Returns string type for a service object of type '<hand_operations-response>"
  "astronaut_controllers/hand_operationsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hand_operations-response)))
  "Returns string type for a service object of type 'hand_operations-response"
  "astronaut_controllers/hand_operationsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hand_operations-response>)))
  "Returns md5sum for a message object of type '<hand_operations-response>"
  "e64cddebc1c701e9b45008b7ec9f9d6d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hand_operations-response)))
  "Returns md5sum for a message object of type 'hand_operations-response"
  "e64cddebc1c701e9b45008b7ec9f9d6d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hand_operations-response>)))
  "Returns full string definition for message of type '<hand_operations-response>"
  (cl:format cl:nil "~%bool succes~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hand_operations-response)))
  "Returns full string definition for message of type 'hand_operations-response"
  (cl:format cl:nil "~%bool succes~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hand_operations-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hand_operations-response>))
  "Converts a ROS message object to a list"
  (cl:list 'hand_operations-response
    (cl:cons ':succes (succes msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'hand_operations)))
  'hand_operations-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'hand_operations)))
  'hand_operations-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hand_operations)))
  "Returns string type for a service object of type '<hand_operations>"
  "astronaut_controllers/hand_operations")