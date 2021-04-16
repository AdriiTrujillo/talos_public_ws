;; Auto-generated. Do not edit!


(when (boundp 'astronaut_controllers::plot_jnt)
  (if (not (find-package "ASTRONAUT_CONTROLLERS"))
    (make-package "ASTRONAUT_CONTROLLERS"))
  (shadow 'plot_jnt (find-package "ASTRONAUT_CONTROLLERS")))
(unless (find-package "ASTRONAUT_CONTROLLERS::PLOT_JNT")
  (make-package "ASTRONAUT_CONTROLLERS::PLOT_JNT"))

(in-package "ROS")
;;//! \htmlinclude plot_jnt.msg.html


(defclass astronaut_controllers::plot_jnt
  :super ros::object
  :slots (_jnt_0 _jnt_1 _jnt_2 _jnt_3 _jnt_4 _jnt_5 _jnt_6 ))

(defmethod astronaut_controllers::plot_jnt
  (:init
   (&key
    ((:jnt_0 __jnt_0) 0.0)
    ((:jnt_1 __jnt_1) 0.0)
    ((:jnt_2 __jnt_2) 0.0)
    ((:jnt_3 __jnt_3) 0.0)
    ((:jnt_4 __jnt_4) 0.0)
    ((:jnt_5 __jnt_5) 0.0)
    ((:jnt_6 __jnt_6) 0.0)
    )
   (send-super :init)
   (setq _jnt_0 (float __jnt_0))
   (setq _jnt_1 (float __jnt_1))
   (setq _jnt_2 (float __jnt_2))
   (setq _jnt_3 (float __jnt_3))
   (setq _jnt_4 (float __jnt_4))
   (setq _jnt_5 (float __jnt_5))
   (setq _jnt_6 (float __jnt_6))
   self)
  (:jnt_0
   (&optional __jnt_0)
   (if __jnt_0 (setq _jnt_0 __jnt_0)) _jnt_0)
  (:jnt_1
   (&optional __jnt_1)
   (if __jnt_1 (setq _jnt_1 __jnt_1)) _jnt_1)
  (:jnt_2
   (&optional __jnt_2)
   (if __jnt_2 (setq _jnt_2 __jnt_2)) _jnt_2)
  (:jnt_3
   (&optional __jnt_3)
   (if __jnt_3 (setq _jnt_3 __jnt_3)) _jnt_3)
  (:jnt_4
   (&optional __jnt_4)
   (if __jnt_4 (setq _jnt_4 __jnt_4)) _jnt_4)
  (:jnt_5
   (&optional __jnt_5)
   (if __jnt_5 (setq _jnt_5 __jnt_5)) _jnt_5)
  (:jnt_6
   (&optional __jnt_6)
   (if __jnt_6 (setq _jnt_6 __jnt_6)) _jnt_6)
  (:serialization-length
   ()
   (+
    ;; float64 _jnt_0
    8
    ;; float64 _jnt_1
    8
    ;; float64 _jnt_2
    8
    ;; float64 _jnt_3
    8
    ;; float64 _jnt_4
    8
    ;; float64 _jnt_5
    8
    ;; float64 _jnt_6
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _jnt_0
       (sys::poke _jnt_0 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _jnt_1
       (sys::poke _jnt_1 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _jnt_2
       (sys::poke _jnt_2 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _jnt_3
       (sys::poke _jnt_3 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _jnt_4
       (sys::poke _jnt_4 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _jnt_5
       (sys::poke _jnt_5 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _jnt_6
       (sys::poke _jnt_6 (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _jnt_0
     (setq _jnt_0 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _jnt_1
     (setq _jnt_1 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _jnt_2
     (setq _jnt_2 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _jnt_3
     (setq _jnt_3 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _jnt_4
     (setq _jnt_4 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _jnt_5
     (setq _jnt_5 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _jnt_6
     (setq _jnt_6 (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get astronaut_controllers::plot_jnt :md5sum-) "3b09b9904d6a381558d8c771bafb8d82")
(setf (get astronaut_controllers::plot_jnt :datatype-) "astronaut_controllers/plot_jnt")
(setf (get astronaut_controllers::plot_jnt :definition-)
      "float64 jnt_0
float64 jnt_1
float64 jnt_2
float64 jnt_3
float64 jnt_4
float64 jnt_5
float64 jnt_6





")



(provide :astronaut_controllers/plot_jnt "3b09b9904d6a381558d8c771bafb8d82")


