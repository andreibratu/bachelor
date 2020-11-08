import 'package:cross/redux/entry.entity.dart';
import 'package:flutter/widgets.dart';

@immutable
class AppState {
  final List<Entry> entries;
  final Entry currEntry;

  const AppState({@required this.entries, @required this.currEntry});
}
