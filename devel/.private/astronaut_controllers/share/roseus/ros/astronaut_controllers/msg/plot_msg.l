;; Auto-generated. Do not edit!


(when (boundp 'astronaut_controllers::plot_msg)
  (if (not (find-package "ASTRONAUT_CONTROLLERS"))
    (make-package "ASTRONAUT_CONTROLLERS"))
  (shadow 'plot_msg (find-package "ASTRONAUT_CONTROLLERS")))
(unless (find-package "ASTRONAUT_CONTROLLERS::PLOT_MSG")
  (make-package "ASTRONAUT_CONTROLLERS::PLOT_MSG"))

(in-package "ROS")
;;//! \htmlinclude plot_msg.msg.html


(defclass astronaut_controllers::plot_msg
  :super ros::object
  :slots (_x_err _y_err _z_err _roll_err _pitch_err _yaw_err ))

(defmethod astronaut_controllers::plot_msg
  (:init
   (&key
    ((:x_err __x_err) 0.0)
    ((:y_err __y_err) 0.0)
    ((:z_err __z_err) 0.0)
    ((:roll_err __roll_err) 0.0)
    ((:pitch_err __pitch_err) 0.0)
    ((:yaw_err __yaw_err) 0.0)
    )
   (send-super :init)
   (setq _x_err (float __x_err))
   (setq _y_err (float __y_err))
   (setq _z_err (float __z_err))
   (setq _roll_err (float __roll_err))
   (setq _pitch_err (float __pitch_err))
   (setq _yaw_err (float __yaw_err))
   self)
  (:x_err
   (&optional __x_err)
   (if __x_err (setq _x_err __x_err)) _x_err)
  (:y_err
   (&optional __y_err)
   (if __y_err (setq _y_err __y_err)) _y_err)
  (:z_err
   (&optional __z_err)
   (if __z_err (setq _z_err __z_err)) _z_err)
  (:roll_err
   (&optional __roll_err)
   (if __roll_err (setq _roll_err __roll_err)) _roll_err)
  (:pitch_err
   (&optional __pitch_err)
   (if __pitch_err (setq _pitch_err __pitch_err)) _pitch_err)
  (:yaw_err
   (&optional __yaw_err)
   (if __yaw_err (setq _yaw_err __yaw_err)) _yaw_err)
  (:serialization-length
   ()
   (+
    ;; float64 _x_err
    8
    ;; float64 _y_err
    8
    ;; float64 _z_err
    8
    ;; float64 _roll_err
    8
    ;; float64 _pitch_err
    8
    ;; float64 _yaw_err
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x_err
       (sys::poke _x_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y_err
       (sys::poke _y_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z_err
       (sys::poke _z_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _roll_err
       (sys::poke _roll_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _pitch_err
       (sys::poke _pitch_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw_err
       (sys::poke _yaw_err (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x_err
     (setq _x_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y_err
     (setq _y_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z_err
     (setq _z_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _roll_err
     (setq _roll_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _pitch_err
     (setq _pitch_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw_err
     (setq _yaw_err (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get astronaut_controllers::plot_msg :md5sum-) "2e3b1b0cf6c1e9ca2b791e3388980632")
(setf (get astronaut_controllers::plot_msg :datatype-) "astronaut_controllers/plot_msg")
(setf (get astronaut_controllers::plot_msg :definition-)
      "float64 x_err
float64 y_err
float64 z_err
float64 roll_err
float64 pitch_err
float64 yaw_err





")



(provide :astronaut_controllers/plot_msg "2e3b1b0cf6c1e9ca2b791e3388980632")


