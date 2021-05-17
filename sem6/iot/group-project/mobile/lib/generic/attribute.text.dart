import 'package:flutter/material.dart';

class AttributeText extends StatelessWidget {
  /*
    Convenience wrapper for solving a generic problem: listing
    properties of an object in UI. Pass an attribute name and
    its value and render text with attribute name bolded.
  */
  static const TextStyle _BOLD = const TextStyle(fontWeight: FontWeight.bold);

  final String attributeName;
  final String attributeValue;
  final Color textColor;

  const AttributeText(
      {Key key, this.attributeName, this.attributeValue, this.textColor})
      : super(key: key);

  TextStyle _getBoldStyle(double fontSize) =>
      (fontSize == null) ? _BOLD : _BOLD.copyWith(fontSize: fontSize);

  @override
  Widget build(BuildContext context) => RichText(
        text: TextSpan(
          // Note: Styles for TextSpans must be explicitly defined.
          // Child text spans will inherit styles from parent
          style: Theme.of(context).textTheme.bodyText1,
          children: <TextSpan>[
            TextSpan(
                text: '$attributeName: ',
                style: _getBoldStyle(null).copyWith(color: textColor)),
            TextSpan(
                text: attributeValue,
                style: Theme.of(context)
                    .textTheme
                    .bodyText1
                    .copyWith(color: textColor)),
          ],
        ),
      );
}
