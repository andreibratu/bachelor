import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:meta/meta.dart';

@immutable
class LogModel {
  final String phrase;
  final List<String> keywords;
  final DateTime logDate;

  LogModel(
      {required this.phrase, required this.keywords, required this.logDate});

  LogModel.fromFirestoreDocument(QueryDocumentSnapshot document)
      : this.phrase = document['phrase'],
        this.keywords = (document['keywords'] as List<dynamic>)
            .map((e) => e as String)
            .toList(),
        this.logDate =
            DateTime.parse(document['timestamp'].toDate().toString());
}
