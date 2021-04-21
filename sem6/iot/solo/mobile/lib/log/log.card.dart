import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:mobile/log/log.model.dart';

class LogCard extends StatelessWidget {
  final LogModel? log;
  final DateTime someDate = DateTime.now();
  static const TextStyle BOLD = const TextStyle(fontWeight: FontWeight.bold);

  TextStyle getBoldStyle(double? fontSize) =>
      (fontSize == null) ? BOLD : BOLD.copyWith(fontSize: fontSize);

  String formatDate(DateTime date) => DateFormat('MMMM d').format(date);

  LogCard({Key? key, this.log}) : super(key: key);

  @override
  Widget build(BuildContext context) => Container(
      height: 200,
      width: double.infinity,
      child: Card(
        color: Colors.white70,
        shadowColor: Colors.blueGrey,
        child: Padding(
          padding: EdgeInsets.all(5),
          child: Row(children: [
            Flexible(
              flex: 4,
              child: Column(
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  RichText(
                    text: TextSpan(
                      // Note: Styles for TextSpans must be explicitly defined.
                      // Child text spans will inherit styles from parent
                      style: Theme.of(context)
                          .textTheme
                          .bodyText1!
                          .copyWith(fontSize: 20),
                      children: <TextSpan>[
                        TextSpan(text: 'Phrase: ', style: getBoldStyle(null)),
                        TextSpan(
                            text:
                                'This is really really cool This is really really cool This is really really cool This is really really cool'),
                      ],
                    ),
                  ),
                  RichText(
                    text: TextSpan(
                      // Note: Styles for TextSpans must be explicitly defined.
                      // Child text spans will inherit styles from parent
                      style: Theme.of(context).textTheme.bodyText1,
                      children: <TextSpan>[
                        TextSpan(text: 'Keywords: ', style: getBoldStyle(null)),
                        TextSpan(
                            text: [
                          'really',
                          'cool',
                          'what',
                          'mega',
                          'cool',
                          'cmf',
                          'super',
                          'csf',
                          'nice'
                        ].join(", ")),
                      ],
                    ),
                  ),
                ],
              ),
            ),
            Flexible(
              flex: 1,
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    DateFormat('HH').format(someDate).toUpperCase(),
                    style: getBoldStyle(30),
                  ),
                  Text(
                    DateFormat('MM').format(someDate).toString(),
                    style: getBoldStyle(30),
                  ),
                  Text(DateFormat('d MMMM').format(someDate).toUpperCase()),
                  Text(someDate.year.toString())
                ],
              ),
            )
          ]),
        ),
      ));
}
