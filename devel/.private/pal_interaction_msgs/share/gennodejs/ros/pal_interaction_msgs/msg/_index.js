
"use strict";

let WebGuiEvent = require('./WebGuiEvent.js');
let TtsMark = require('./TtsMark.js');
let ASRStatus = require('./ASRStatus.js');
let ASRLanguage = require('./ASRLanguage.js');
let ASRLangModelMngmt = require('./ASRLangModelMngmt.js');
let Input = require('./Input.js');
let VoiceActivity = require('./VoiceActivity.js');
let asrresult = require('./asrresult.js');
let asrupdate = require('./asrupdate.js');
let TTSstate = require('./TTSstate.js');
let ASRActivation = require('./ASRActivation.js');
let actiontag = require('./actiontag.js');
let AudioDeviceDescription = require('./AudioDeviceDescription.js');
let TtsText = require('./TtsText.js');
let AudioPlayerState = require('./AudioPlayerState.js');
let I18nText = require('./I18nText.js');
let ASRSrvRequest = require('./ASRSrvRequest.js');
let ASREvent = require('./ASREvent.js');
let InputArgument = require('./InputArgument.js');
let audiosignal = require('./audiosignal.js');
let ASRSrvResponse = require('./ASRSrvResponse.js');
let DirectionOfArrival = require('./DirectionOfArrival.js');
let EnablingSoundLocalisation = require('./EnablingSoundLocalisation.js');
let I18nArgument = require('./I18nArgument.js');
let ASRFileAction = require('./ASRFileAction.js');
let TtsActionGoal = require('./TtsActionGoal.js');
let TtsActionFeedback = require('./TtsActionFeedback.js');
let SoundFeedback = require('./SoundFeedback.js');
let ASRFileResult = require('./ASRFileResult.js');
let ASRFileActionFeedback = require('./ASRFileActionFeedback.js');
let TtsFeedback = require('./TtsFeedback.js');
let AudioPlayActionGoal = require('./AudioPlayActionGoal.js');
let AudioPlayResult = require('./AudioPlayResult.js');
let ASRFileActionResult = require('./ASRFileActionResult.js');
let SoundGoal = require('./SoundGoal.js');
let TtsResult = require('./TtsResult.js');
let AudioPlayActionResult = require('./AudioPlayActionResult.js');
let ASRFileGoal = require('./ASRFileGoal.js');
let AudioPlayAction = require('./AudioPlayAction.js');
let SoundActionGoal = require('./SoundActionGoal.js');
let SoundActionFeedback = require('./SoundActionFeedback.js');
let TtsAction = require('./TtsAction.js');
let SoundAction = require('./SoundAction.js');
let TtsActionResult = require('./TtsActionResult.js');
let SoundActionResult = require('./SoundActionResult.js');
let AudioPlayActionFeedback = require('./AudioPlayActionFeedback.js');
let ASRFileActionGoal = require('./ASRFileActionGoal.js');
let AudioPlayFeedback = require('./AudioPlayFeedback.js');
let ASRFileFeedback = require('./ASRFileFeedback.js');
let AudioPlayGoal = require('./AudioPlayGoal.js');
let TtsGoal = require('./TtsGoal.js');
let SoundResult = require('./SoundResult.js');

module.exports = {
  WebGuiEvent: WebGuiEvent,
  TtsMark: TtsMark,
  ASRStatus: ASRStatus,
  ASRLanguage: ASRLanguage,
  ASRLangModelMngmt: ASRLangModelMngmt,
  Input: Input,
  VoiceActivity: VoiceActivity,
  asrresult: asrresult,
  asrupdate: asrupdate,
  TTSstate: TTSstate,
  ASRActivation: ASRActivation,
  actiontag: actiontag,
  AudioDeviceDescription: AudioDeviceDescription,
  TtsText: TtsText,
  AudioPlayerState: AudioPlayerState,
  I18nText: I18nText,
  ASRSrvRequest: ASRSrvRequest,
  ASREvent: ASREvent,
  InputArgument: InputArgument,
  audiosignal: audiosignal,
  ASRSrvResponse: ASRSrvResponse,
  DirectionOfArrival: DirectionOfArrival,
  EnablingSoundLocalisation: EnablingSoundLocalisation,
  I18nArgument: I18nArgument,
  ASRFileAction: ASRFileAction,
  TtsActionGoal: TtsActionGoal,
  TtsActionFeedback: TtsActionFeedback,
  SoundFeedback: SoundFeedback,
  ASRFileResult: ASRFileResult,
  ASRFileActionFeedback: ASRFileActionFeedback,
  TtsFeedback: TtsFeedback,
  AudioPlayActionGoal: AudioPlayActionGoal,
  AudioPlayResult: AudioPlayResult,
  ASRFileActionResult: ASRFileActionResult,
  SoundGoal: SoundGoal,
  TtsResult: TtsResult,
  AudioPlayActionResult: AudioPlayActionResult,
  ASRFileGoal: ASRFileGoal,
  AudioPlayAction: AudioPlayAction,
  SoundActionGoal: SoundActionGoal,
  SoundActionFeedback: SoundActionFeedback,
  TtsAction: TtsAction,
  SoundAction: SoundAction,
  TtsActionResult: TtsActionResult,
  SoundActionResult: SoundActionResult,
  AudioPlayActionFeedback: AudioPlayActionFeedback,
  ASRFileActionGoal: ASRFileActionGoal,
  AudioPlayFeedback: AudioPlayFeedback,
  ASRFileFeedback: ASRFileFeedback,
  AudioPlayGoal: AudioPlayGoal,
  TtsGoal: TtsGoal,
  SoundResult: SoundResult,
};
