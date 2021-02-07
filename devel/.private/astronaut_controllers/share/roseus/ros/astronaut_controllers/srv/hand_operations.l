;; Auto-generated. Do not edit!


(when (boundp 'astronaut_controllers::hand_operations)
  (if (not (find-package "ASTRONAUT_CONTROLLERS"))
    (make-package "ASTRONAUT_CONTROLLERS"))
  (shadow 'hand_operations (find-package "ASTRONAUT_CONTROLLERS")))
(unless (find-package "ASTRONAUT_CONTROLLERS::HAND_OPERATIONS")
  (make-package "ASTRONAUT_CONTROLLERS::HAND_OPERATIONS"))
(unless (find-package "ASTRONAUT_CONTROLLERS::HAND_OPERATIONSREQUEST")
  (make-package "ASTRONAUT_CONTROLLERS::HAND_OPERATIONSREQUEST"))
(unless (find-package "ASTRONAUT_CONTROLLERS::HAND_OPERATIONSRESPONSE")
  (make-package "ASTRONAUT_CONTROLLERS::HAND_OPERATIONSRESPONSE"))

(in-package "ROS")





(defclass astronaut_controllers::hand_operationsRequest
  :super ros::object
  :slots (_operation _hand ))

(defmethod astronaut_controllers::hand_operationsRequest
  (:init
   (&key
    ((:operation __operation) "")
    ((:hand __hand) "")
    )
   (send-super :init)
   (setq _operation (string __operation))
   (setq _hand (string __hand))
   self)
  (:operation
   (&optional __operation)
   (if __operation (setq _operation __operation)) _operation)
  (:hand
   (&optional __hand)
   (if __hand (setq _hand __hand)) _hand)
  (:serialization-length
   ()
   (+
    ;; string _operation
    4 (length _operation)
    ;; string _hand
    4 (length _hand)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _operation
       (write-long (length _operation) s) (princ _operation s)
     ;; string _hand
       (write-long (length _hand) s) (princ _hand s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _operation
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _operation (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _hand
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _hand (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass astronaut_controllers::hand_operationsResponse
  :super ros::object
  :slots (_succes ))

(defmethod astronaut_controllers::hand_operationsResponse
  (:init
   (&key
    ((:succes __succes) nil)
    )
   (send-super :init)
   (setq _succes __succes)
   self)
  (:succes
   (&optional __succes)
   (if __succes (setq _succes __succes)) _succes)
  (:serialization-length
   ()
   (+
    ;; bool _succes
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _succes
       (if _succes (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _succes
     (setq _succes (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass astronaut_controllers::hand_operations
  :super ros::object
  :slots ())

(setf (get astronaut_controllers::hand_operations :md5sum-) "e64cddebc1c701e9b45008b7ec9f9d6d")
(setf (get astronaut_controllers::hand_operations :datatype-) "astronaut_controllers/hand_operations")
(setf (get astronaut_controllers::hand_operations :request) astronaut_controllers::hand_operationsRequest)
(setf (get astronaut_controllers::hand_operations :response) astronaut_controllers::hand_operationsResponse)

(defmethod astronaut_controllers::hand_operationsRequest
  (:response () (instance astronaut_controllers::hand_operationsResponse :init)))

(setf (get astronaut_controllers::hand_operationsRequest :md5sum-) "e64cddebc1c701e9b45008b7ec9f9d6d")
(setf (get astronaut_controllers::hand_operationsRequest :datatype-) "astronaut_controllers/hand_operationsRequest")
(setf (get astronaut_controllers::hand_operationsRequest :definition-)
      "string operation
string hand

---

bool succes
")

(setf (get astronaut_controllers::hand_operationsResponse :md5sum-) "e64cddebc1c701e9b45008b7ec9f9d6d")
(setf (get astronaut_controllers::hand_operationsResponse :datatype-) "astronaut_controllers/hand_operationsResponse")
(setf (get astronaut_controllers::hand_operationsResponse :definition-)
      "string operation
string hand

---

bool succes
")



(provide :astronaut_controllers/hand_operations "e64cddebc1c701e9b45008b7ec9f9d6d")


