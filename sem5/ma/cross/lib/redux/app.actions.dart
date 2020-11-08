import 'entry.entity.dart';

class EntryAction {}

class AddEntryAction extends EntryAction {
  final Entry newEntry;

  AddEntryAction({this.newEntry});
}

class DeleteEntryAction extends EntryAction {
  final int deleteId;

  DeleteEntryAction({this.deleteId});
}

class EditEntryAction extends EntryAction {
  final Entry editedEntry;

  EditEntryAction({this.editedEntry});
}

class SetCurrentEntryAction extends EntryAction {
  final Entry currEntry;

  SetCurrentEntryAction({this.currEntry});
}
