
"use strict";

let actiontag = require('./actiontag.js');
let ASRSrvResponse = require('./ASRSrvResponse.js');
let ASREvent = require('./ASREvent.js');
let TtsText = require('./TtsText.js');
let TTSstate = require('./TTSstate.js');
let ASRSrvRequest = require('./ASRSrvRequest.js');
let InputArgument = require('./InputArgument.js');
let ASRLanguage = require('./ASRLanguage.js');
let audiosignal = require('./audiosignal.js');
let asrresult = require('./asrresult.js');
let Input = require('./Input.js');
let ASRActivation = require('./ASRActivation.js');
let VoiceActivity = require('./VoiceActivity.js');
let DirectionOfArrival = require('./DirectionOfArrival.js');
let I18nText = require('./I18nText.js');
let ASRStatus = require('./ASRStatus.js');
let AudioDeviceDescription = require('./AudioDeviceDescription.js');
let WebGuiEvent = require('./WebGuiEvent.js');
let ASRLangModelMngmt = require('./ASRLangModelMngmt.js');
let I18nArgument = require('./I18nArgument.js');
let asrupdate = require('./asrupdate.js');
let EnablingSoundLocalisation = require('./EnablingSoundLocalisation.js');
let AudioPlayerState = require('./AudioPlayerState.js');
let TtsMark = require('./TtsMark.js');
let AudioPlayFeedback = require('./AudioPlayFeedback.js');
let AudioPlayGoal = require('./AudioPlayGoal.js');
let ASRFileActionFeedback = require('./ASRFileActionFeedback.js');
let TtsGoal = require('./TtsGoal.js');
let TtsActionResult = require('./TtsActionResult.js');
let TtsActionFeedback = require('./TtsActionFeedback.js');
let AudioPlayActionGoal = require('./AudioPlayActionGoal.js');
let SoundActionGoal = require('./SoundActionGoal.js');
let AudioPlayActionFeedback = require('./AudioPlayActionFeedback.js');
let ASRFileGoal = require('./ASRFileGoal.js');
let SoundActionFeedback = require('./SoundActionFeedback.js');
let SoundActionResult = require('./SoundActionResult.js');
let AudioPlayAction = require('./AudioPlayAction.js');
let SoundAction = require('./SoundAction.js');
let ASRFileAction = require('./ASRFileAction.js');
let ASRFileActionResult = require('./ASRFileActionResult.js');
let TtsFeedback = require('./TtsFeedback.js');
let AudioPlayResult = require('./AudioPlayResult.js');
let ASRFileResult = require('./ASRFileResult.js');
let TtsAction = require('./TtsAction.js');
let SoundFeedback = require('./SoundFeedback.js');
let SoundGoal = require('./SoundGoal.js');
let ASRFileActionGoal = require('./ASRFileActionGoal.js');
let SoundResult = require('./SoundResult.js');
let TtsResult = require('./TtsResult.js');
let TtsActionGoal = require('./TtsActionGoal.js');
let AudioPlayActionResult = require('./AudioPlayActionResult.js');
let ASRFileFeedback = require('./ASRFileFeedback.js');

module.exports = {
  actiontag: actiontag,
  ASRSrvResponse: ASRSrvResponse,
  ASREvent: ASREvent,
  TtsText: TtsText,
  TTSstate: TTSstate,
  ASRSrvRequest: ASRSrvRequest,
  InputArgument: InputArgument,
  ASRLanguage: ASRLanguage,
  audiosignal: audiosignal,
  asrresult: asrresult,
  Input: Input,
  ASRActivation: ASRActivation,
  VoiceActivity: VoiceActivity,
  DirectionOfArrival: DirectionOfArrival,
  I18nText: I18nText,
  ASRStatus: ASRStatus,
  AudioDeviceDescription: AudioDeviceDescription,
  WebGuiEvent: WebGuiEvent,
  ASRLangModelMngmt: ASRLangModelMngmt,
  I18nArgument: I18nArgument,
  asrupdate: asrupdate,
  EnablingSoundLocalisation: EnablingSoundLocalisation,
  AudioPlayerState: AudioPlayerState,
  TtsMark: TtsMark,
  AudioPlayFeedback: AudioPlayFeedback,
  AudioPlayGoal: AudioPlayGoal,
  ASRFileActionFeedback: ASRFileActionFeedback,
  TtsGoal: TtsGoal,
  TtsActionResult: TtsActionResult,
  TtsActionFeedback: TtsActionFeedback,
  AudioPlayActionGoal: AudioPlayActionGoal,
  SoundActionGoal: SoundActionGoal,
  AudioPlayActionFeedback: AudioPlayActionFeedback,
  ASRFileGoal: ASRFileGoal,
  SoundActionFeedback: SoundActionFeedback,
  SoundActionResult: SoundActionResult,
  AudioPlayAction: AudioPlayAction,
  SoundAction: SoundAction,
  ASRFileAction: ASRFileAction,
  ASRFileActionResult: ASRFileActionResult,
  TtsFeedback: TtsFeedback,
  AudioPlayResult: AudioPlayResult,
  ASRFileResult: ASRFileResult,
  TtsAction: TtsAction,
  SoundFeedback: SoundFeedback,
  SoundGoal: SoundGoal,
  ASRFileActionGoal: ASRFileActionGoal,
  SoundResult: SoundResult,
  TtsResult: TtsResult,
  TtsActionGoal: TtsActionGoal,
  AudioPlayActionResult: AudioPlayActionResult,
  ASRFileFeedback: ASRFileFeedback,
};
