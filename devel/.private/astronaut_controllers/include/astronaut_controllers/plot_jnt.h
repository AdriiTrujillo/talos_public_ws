// Generated by gencpp from file astronaut_controllers/plot_jnt.msg
// DO NOT EDIT!


#ifndef ASTRONAUT_CONTROLLERS_MESSAGE_PLOT_JNT_H
#define ASTRONAUT_CONTROLLERS_MESSAGE_PLOT_JNT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace astronaut_controllers
{
template <class ContainerAllocator>
struct plot_jnt_
{
  typedef plot_jnt_<ContainerAllocator> Type;

  plot_jnt_()
    : jnt_0(0.0)
    , jnt_1(0.0)
    , jnt_2(0.0)
    , jnt_3(0.0)
    , jnt_4(0.0)
    , jnt_5(0.0)
    , jnt_6(0.0)  {
    }
  plot_jnt_(const ContainerAllocator& _alloc)
    : jnt_0(0.0)
    , jnt_1(0.0)
    , jnt_2(0.0)
    , jnt_3(0.0)
    , jnt_4(0.0)
    , jnt_5(0.0)
    , jnt_6(0.0)  {
  (void)_alloc;
    }



   typedef double _jnt_0_type;
  _jnt_0_type jnt_0;

   typedef double _jnt_1_type;
  _jnt_1_type jnt_1;

   typedef double _jnt_2_type;
  _jnt_2_type jnt_2;

   typedef double _jnt_3_type;
  _jnt_3_type jnt_3;

   typedef double _jnt_4_type;
  _jnt_4_type jnt_4;

   typedef double _jnt_5_type;
  _jnt_5_type jnt_5;

   typedef double _jnt_6_type;
  _jnt_6_type jnt_6;





  typedef boost::shared_ptr< ::astronaut_controllers::plot_jnt_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::astronaut_controllers::plot_jnt_<ContainerAllocator> const> ConstPtr;

}; // struct plot_jnt_

typedef ::astronaut_controllers::plot_jnt_<std::allocator<void> > plot_jnt;

typedef boost::shared_ptr< ::astronaut_controllers::plot_jnt > plot_jntPtr;
typedef boost::shared_ptr< ::astronaut_controllers::plot_jnt const> plot_jntConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::astronaut_controllers::plot_jnt_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace astronaut_controllers

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'astronaut_controllers': ['/home/adrii/talos_public_ws/src/talos_astronaut/astronaut_controllers/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::astronaut_controllers::plot_jnt_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::astronaut_controllers::plot_jnt_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::astronaut_controllers::plot_jnt_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3b09b9904d6a381558d8c771bafb8d82";
  }

  static const char* value(const ::astronaut_controllers::plot_jnt_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3b09b9904d6a3815ULL;
  static const uint64_t static_value2 = 0x58d8c771bafb8d82ULL;
};

template<class ContainerAllocator>
struct DataType< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
{
  static const char* value()
  {
    return "astronaut_controllers/plot_jnt";
  }

  static const char* value(const ::astronaut_controllers::plot_jnt_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 jnt_0\n\
float64 jnt_1\n\
float64 jnt_2\n\
float64 jnt_3\n\
float64 jnt_4\n\
float64 jnt_5\n\
float64 jnt_6\n\
\n\
\n\
\n\
\n\
";
  }

  static const char* value(const ::astronaut_controllers::plot_jnt_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.jnt_0);
      stream.next(m.jnt_1);
      stream.next(m.jnt_2);
      stream.next(m.jnt_3);
      stream.next(m.jnt_4);
      stream.next(m.jnt_5);
      stream.next(m.jnt_6);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct plot_jnt_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::astronaut_controllers::plot_jnt_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::astronaut_controllers::plot_jnt_<ContainerAllocator>& v)
  {
    s << indent << "jnt_0: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_0);
    s << indent << "jnt_1: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_1);
    s << indent << "jnt_2: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_2);
    s << indent << "jnt_3: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_3);
    s << indent << "jnt_4: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_4);
    s << indent << "jnt_5: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_5);
    s << indent << "jnt_6: ";
    Printer<double>::stream(s, indent + "  ", v.jnt_6);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ASTRONAUT_CONTROLLERS_MESSAGE_PLOT_JNT_H