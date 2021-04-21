class LogModel {
  final String recognizedText;
  final List<String> keywords;
  final DateTime logDate;

  LogModel(
      {required this.recognizedText,
      required this.keywords,
      required this.logDate});
}
