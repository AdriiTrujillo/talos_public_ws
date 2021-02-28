
"use strict";

let DisableEmergency = require('./DisableEmergency.js')
let GetPOI = require('./GetPOI.js')
let RenameMap = require('./RenameMap.js')
let SafetyZone = require('./SafetyZone.js')
let ListMaps = require('./ListMaps.js')
let GetMapConfiguration = require('./GetMapConfiguration.js')
let ChangeBuilding = require('./ChangeBuilding.js')
let FinalApproachPose = require('./FinalApproachPose.js')
let Acknowledgment = require('./Acknowledgment.js')
let GetSubMap = require('./GetSubMap.js')
let SetMapConfiguration = require('./SetMapConfiguration.js')
let SetSubMapFloor = require('./SetSubMapFloor.js')
let VisualLocRecognize = require('./VisualLocRecognize.js')
let SaveMap = require('./SaveMap.js')
let SetPOI = require('./SetPOI.js')
let GetNodes = require('./GetNodes.js')

module.exports = {
  DisableEmergency: DisableEmergency,
  GetPOI: GetPOI,
  RenameMap: RenameMap,
  SafetyZone: SafetyZone,
  ListMaps: ListMaps,
  GetMapConfiguration: GetMapConfiguration,
  ChangeBuilding: ChangeBuilding,
  FinalApproachPose: FinalApproachPose,
  Acknowledgment: Acknowledgment,
  GetSubMap: GetSubMap,
  SetMapConfiguration: SetMapConfiguration,
  SetSubMapFloor: SetSubMapFloor,
  VisualLocRecognize: VisualLocRecognize,
  SaveMap: SaveMap,
  SetPOI: SetPOI,
  GetNodes: GetNodes,
};
