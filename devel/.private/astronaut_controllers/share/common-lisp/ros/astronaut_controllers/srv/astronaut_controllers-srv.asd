
(cl:in-package :asdf)

(defsystem "astronaut_controllers-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "hand_operations" :depends-on ("_package_hand_operations"))
    (:file "_package_hand_operations" :depends-on ("_package"))
  ))