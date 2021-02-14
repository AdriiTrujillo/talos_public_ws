
(cl:in-package :asdf)

(defsystem "astronaut_controllers-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "target_frame" :depends-on ("_package_target_frame"))
    (:file "_package_target_frame" :depends-on ("_package"))
  ))