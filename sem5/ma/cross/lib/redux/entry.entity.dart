import 'package:flutter/widgets.dart';

class Entry {
  static var globalId = 0;
  int id;
  String title;
  String description;
  DateTime entryDate;
  Color color;

  Entry(
      {@required this.title,
      @required this.description,
      @required this.color}) {
    this.id = Entry.globalId;
    Entry.globalId += 1;
    this.entryDate = DateTime.now();
  }

  Entry.copy(Entry entry) {
    this.id = entry.id;
    this.title = entry.title;
    this.description = entry.description;
    this.entryDate = entry.entryDate;
    this.color = entry.color;
  }
}
