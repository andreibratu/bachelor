import 'package:cross/redux/app.actions.dart';
import 'package:cross/redux/app.state.dart';

import 'entry.entity.dart';

AppState appReducer(AppState oldState, dynamic action) {
  List<Entry> newEntries = List<Entry>.from(oldState.entries);
  if (action is AddEntryAction) {
    newEntries.add(action.newEntry);
    return AppState(entries: newEntries, currEntry: oldState.currEntry);
  }
  if (action is DeleteEntryAction) {
    newEntries.removeWhere((element) => element.id == action.deleteId);
    return AppState(entries: newEntries, currEntry: oldState.currEntry);
  }
  if (action is EditEntryAction) {
    newEntries.removeWhere((element) => element.id == action.editedEntry.id);
    newEntries.add(action.editedEntry);
    return AppState(entries: newEntries, currEntry: oldState.currEntry);
  }
  if (action is SetCurrentEntryAction) {
    return AppState(entries: newEntries, currEntry: action.currEntry);
  }
  return null;
}
