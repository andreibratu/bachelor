import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:meta/meta.dart';

@immutable
class KeywordModel {
  final String keyword;
  final int count;

  KeywordModel({required this.keyword, required this.count});

  KeywordModel.fromFirestoreDocument(QueryDocumentSnapshot document)
      : this.keyword = document['keyword'],
        this.count = document['count'];
}
