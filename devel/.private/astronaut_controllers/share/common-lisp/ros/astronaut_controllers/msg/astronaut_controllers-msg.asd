
(cl:in-package :asdf)

(defsystem "astronaut_controllers-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "plot_jnt" :depends-on ("_package_plot_jnt"))
    (:file "_package_plot_jnt" :depends-on ("_package"))
    (:file "plot_msg" :depends-on ("_package_plot_msg"))
    (:file "_package_plot_msg" :depends-on ("_package"))
    (:file "target_frame" :depends-on ("_package_target_frame"))
    (:file "_package_target_frame" :depends-on ("_package"))
  ))