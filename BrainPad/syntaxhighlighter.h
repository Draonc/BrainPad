        #ifndef SYNTAXHIGHLIGHTER_H
        #define SYNTAXHIGHLIGHTER_H

        #include <QSyntaxHighlighter>

        #include <QHash>
        #include <QTextCharFormat>

        class QTextDocument;

        class Highlighter : public QSyntaxHighlighter
        {
            Q_OBJECT

        public:
            Highlighter(QTextDocument *parent = 0);

        protected:
            void highlightBlock(const QString &text);

        public:
            void highlightError(int errors[]);

        private:
            struct HighlightingRule
            {
                QRegExp pattern;
                QTextCharFormat format;
            };
            QVector<HighlightingRule> highlightingRules;

            QRegExp commentStartExpression;
            QRegExp commentEndExpression;

            QTextCharFormat errorFormat;//Fuck ups
            QTextCharFormat whilerightFormat;//[
            QTextCharFormat whileleftFormat;//]
            QTextCharFormat commentFormat;//Anything else
            QTextCharFormat pointerrightFormat;//>
            QTextCharFormat pointerleftFormat;//<
            QTextCharFormat plusFormat;//+
            QTextCharFormat minusFormat;//-
            QTextCharFormat outputFormat; //.
            QTextCharFormat inputFormat; //,
        };

        #endif
