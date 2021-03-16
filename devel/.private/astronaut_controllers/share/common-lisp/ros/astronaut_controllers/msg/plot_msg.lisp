; Auto-generated. Do not edit!


(cl:in-package astronaut_controllers-msg)


;//! \htmlinclude plot_msg.msg.html

(cl:defclass <plot_msg> (roslisp-msg-protocol:ros-message)
  ((x_err
    :reader x_err
    :initarg :x_err
    :type cl:float
    :initform 0.0)
   (y_err
    :reader y_err
    :initarg :y_err
    :type cl:float
    :initform 0.0)
   (z_err
    :reader z_err
    :initarg :z_err
    :type cl:float
    :initform 0.0)
   (roll_err
    :reader roll_err
    :initarg :roll_err
    :type cl:float
    :initform 0.0)
   (pitch_err
    :reader pitch_err
    :initarg :pitch_err
    :type cl:float
    :initform 0.0)
   (yaw_err
    :reader yaw_err
    :initarg :yaw_err
    :type cl:float
    :initform 0.0))
)

(cl:defclass plot_msg (<plot_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <plot_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'plot_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name astronaut_controllers-msg:<plot_msg> is deprecated: use astronaut_controllers-msg:plot_msg instead.")))

(cl:ensure-generic-function 'x_err-val :lambda-list '(m))
(cl:defmethod x_err-val ((m <plot_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:x_err-val is deprecated.  Use astronaut_controllers-msg:x_err instead.")
  (x_err m))

(cl:ensure-generic-function 'y_err-val :lambda-list '(m))
(cl:defmethod y_err-val ((m <plot_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:y_err-val is deprecated.  Use astronaut_controllers-msg:y_err instead.")
  (y_err m))

(cl:ensure-generic-function 'z_err-val :lambda-list '(m))
(cl:defmethod z_err-val ((m <plot_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:z_err-val is deprecated.  Use astronaut_controllers-msg:z_err instead.")
  (z_err m))

(cl:ensure-generic-function 'roll_err-val :lambda-list '(m))
(cl:defmethod roll_err-val ((m <plot_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:roll_err-val is deprecated.  Use astronaut_controllers-msg:roll_err instead.")
  (roll_err m))

(cl:ensure-generic-function 'pitch_err-val :lambda-list '(m))
(cl:defmethod pitch_err-val ((m <plot_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:pitch_err-val is deprecated.  Use astronaut_controllers-msg:pitch_err instead.")
  (pitch_err m))

(cl:ensure-generic-function 'yaw_err-val :lambda-list '(m))
(cl:defmethod yaw_err-val ((m <plot_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader astronaut_controllers-msg:yaw_err-val is deprecated.  Use astronaut_controllers-msg:yaw_err instead.")
  (yaw_err m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <plot_msg>) ostream)
  "Serializes a message object of type '<plot_msg>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'z_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'roll_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'pitch_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'yaw_err))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <plot_msg>) istream)
  "Deserializes a message object of type '<plot_msg>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x_err) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y_err) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z_err) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'roll_err) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch_err) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_err) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<plot_msg>)))
  "Returns string type for a message object of type '<plot_msg>"
  "astronaut_controllers/plot_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'plot_msg)))
  "Returns string type for a message object of type 'plot_msg"
  "astronaut_controllers/plot_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<plot_msg>)))
  "Returns md5sum for a message object of type '<plot_msg>"
  "2e3b1b0cf6c1e9ca2b791e3388980632")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'plot_msg)))
  "Returns md5sum for a message object of type 'plot_msg"
  "2e3b1b0cf6c1e9ca2b791e3388980632")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<plot_msg>)))
  "Returns full string definition for message of type '<plot_msg>"
  (cl:format cl:nil "float64 x_err~%float64 y_err~%float64 z_err~%float64 roll_err~%float64 pitch_err~%float64 yaw_err~%~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'plot_msg)))
  "Returns full string definition for message of type 'plot_msg"
  (cl:format cl:nil "float64 x_err~%float64 y_err~%float64 z_err~%float64 roll_err~%float64 pitch_err~%float64 yaw_err~%~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <plot_msg>))
  (cl:+ 0
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <plot_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'plot_msg
    (cl:cons ':x_err (x_err msg))
    (cl:cons ':y_err (y_err msg))
    (cl:cons ':z_err (z_err msg))
    (cl:cons ':roll_err (roll_err msg))
    (cl:cons ':pitch_err (pitch_err msg))
    (cl:cons ':yaw_err (yaw_err msg))
))
