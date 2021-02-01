
"use strict";

let ListMaps = require('./ListMaps.js')
let GetMapConfiguration = require('./GetMapConfiguration.js')
let GetNodes = require('./GetNodes.js')
let SetSubMapFloor = require('./SetSubMapFloor.js')
let GetPOI = require('./GetPOI.js')
let VisualLocRecognize = require('./VisualLocRecognize.js')
let SaveMap = require('./SaveMap.js')
let SafetyZone = require('./SafetyZone.js')
let SetMapConfiguration = require('./SetMapConfiguration.js')
let ChangeBuilding = require('./ChangeBuilding.js')
let RenameMap = require('./RenameMap.js')
let GetSubMap = require('./GetSubMap.js')
let SetPOI = require('./SetPOI.js')
let FinalApproachPose = require('./FinalApproachPose.js')
let Acknowledgment = require('./Acknowledgment.js')
let DisableEmergency = require('./DisableEmergency.js')

module.exports = {
  ListMaps: ListMaps,
  GetMapConfiguration: GetMapConfiguration,
  GetNodes: GetNodes,
  SetSubMapFloor: SetSubMapFloor,
  GetPOI: GetPOI,
  VisualLocRecognize: VisualLocRecognize,
  SaveMap: SaveMap,
  SafetyZone: SafetyZone,
  SetMapConfiguration: SetMapConfiguration,
  ChangeBuilding: ChangeBuilding,
  RenameMap: RenameMap,
  GetSubMap: GetSubMap,
  SetPOI: SetPOI,
  FinalApproachPose: FinalApproachPose,
  Acknowledgment: Acknowledgment,
  DisableEmergency: DisableEmergency,
};
