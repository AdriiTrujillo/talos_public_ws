; Auto-generated. Do not edit!


(cl:in-package astronaut_controllers-msg)


;//! \htmlinclude plot_jnt.msg.html

(cl:defclass <plot_jnt> (roslisp-msg-protocol:ros-message)
  ((jnt_0
    :reader jnt_0
    :initarg :jnt_0
    :type cl:float
    :initform 0.0)
   (jnt_1
    :reader jnt_1
    :initarg :jnt_1
    :type cl:float
    :initform 0.0)
   (jnt_2
    :reader jnt_2
    :initarg :jnt_2
    :type cl:float
    :initform 0.0)
   (jnt_3
    :reader jnt_3
    :initarg :jnt_3
    :type cl:float
    :initform 0.0)
   (jnt_4
    :reader jnt_4
    :initarg :jnt_4
    :type cl:float
    :initform 0.0)
   (jnt_5
    :reader jnt_5
    :initarg :jnt_5
    :type cl:float
    :initform 0.0)
   (jnt_6
    :reader jnt_6
    :initarg :jnt_6
    :type cl:float
    :initform 0.0))
)

(cl:defclass plot_jnt (<plot_jnt>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <plot_jnt>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'plot_jnt)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name astronaut_controllers-msg:<plot_jnt> is deprecated: use astronaut_controllers-msg:plot_jnt instead.")))

(cl:ensure-generic-function 'jnt_0-val :lambda-list '(m))
(cl:defmethod jnt_0-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_0-val is deprecated.  Use astronaut_controllers-msg:jnt_0 instead.")
  (jnt_0 m))

(cl:ensure-generic-function 'jnt_1-val :lambda-list '(m))
(cl:defmethod jnt_1-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_1-val is deprecated.  Use astronaut_controllers-msg:jnt_1 instead.")
  (jnt_1 m))

(cl:ensure-generic-function 'jnt_2-val :lambda-list '(m))
(cl:defmethod jnt_2-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_2-val is deprecated.  Use astronaut_controllers-msg:jnt_2 instead.")
  (jnt_2 m))

(cl:ensure-generic-function 'jnt_3-val :lambda-list '(m))
(cl:defmethod jnt_3-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_3-val is deprecated.  Use astronaut_controllers-msg:jnt_3 instead.")
  (jnt_3 m))

(cl:ensure-generic-function 'jnt_4-val :lambda-list '(m))
(cl:defmethod jnt_4-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_4-val is deprecated.  Use astronaut_controllers-msg:jnt_4 instead.")
  (jnt_4 m))

(cl:ensure-generic-function 'jnt_5-val :lambda-list '(m))
(cl:defmethod jnt_5-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_5-val is deprecated.  Use astronaut_controllers-msg:jnt_5 instead.")
  (jnt_5 m))

(cl:ensure-generic-function 'jnt_6-val :lambda-list '(m))
(cl:defmethod jnt_6-val ((m <plot_jnt>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:jnt_6-val is deprecated.  Use astronaut_controllers-msg:jnt_6 instead.")
  (jnt_6 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <plot_jnt>) ostream)
  "Serializes a message object of type '<plot_jnt>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_4))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_5))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'jnt_6))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <plot_jnt>) istream)
  "Deserializes a message object of type '<plot_jnt>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_0) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_1) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_2) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_3) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_4) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_5) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'jnt_6) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<plot_jnt>)))
  "Returns string type for a message object of type '<plot_jnt>"
  "astronaut_controllers/plot_jnt")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'plot_jnt)))
  "Returns string type for a message object of type 'plot_jnt"
  "astronaut_controllers/plot_jnt")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<plot_jnt>)))
  "Returns md5sum for a message object of type '<plot_jnt>"
  "3b09b9904d6a381558d8c771bafb8d82")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'plot_jnt)))
  "Returns md5sum for a message object of type 'plot_jnt"
  "3b09b9904d6a381558d8c771bafb8d82")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<plot_jnt>)))
  "Returns full string definition for message of type '<plot_jnt>"
  (cl:format cl:nil "float64 jnt_0~%float64 jnt_1~%float64 jnt_2~%float64 jnt_3~%float64 jnt_4~%float64 jnt_5~%float64 jnt_6~%~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'plot_jnt)))
  "Returns full string definition for message of type 'plot_jnt"
  (cl:format cl:nil "float64 jnt_0~%float64 jnt_1~%float64 jnt_2~%float64 jnt_3~%float64 jnt_4~%float64 jnt_5~%float64 jnt_6~%~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <plot_jnt>))
  (cl:+ 0
     8
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <plot_jnt>))
  "Converts a ROS message object to a list"
  (cl:list 'plot_jnt
    (cl:cons ':jnt_0 (jnt_0 msg))
    (cl:cons ':jnt_1 (jnt_1 msg))
    (cl:cons ':jnt_2 (jnt_2 msg))
    (cl:cons ':jnt_3 (jnt_3 msg))
    (cl:cons ':jnt_4 (jnt_4 msg))
    (cl:cons ':jnt_5 (jnt_5 msg))
    (cl:cons ':jnt_6 (jnt_6 msg))
))
