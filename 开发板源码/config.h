#ifndef CONFIG_H
#define CONFIG_H



#define PUSHBUTTON_STYLE        "QPushButton {\
                                font-size: 16px;\
                                background-color: transparent;\
                                font-family: \"Microsoft YaHei\";\
                                font-size: 14px;\
                                font-style: italic;\
                                font-weight: bold;\
                                color: #5072c0;\
                                font: bold italic 18px \"Microsoft YaHei\";\
                                text-align: left center;\
                                left right top bottom center;\
                                padding-left: 10px;\
                                padding-top: 8px;\
                                padding-right: 7px;\
                                padding-bottom: 9px;\
                                border-style: solid;\
                                border-width: 2px;\
                                border-color: transparent;\
                                border: 2px solid transparent;\
                                border-top-style: solid;\
                                border-top-width: 2px; \
                                border-top-color: transparent; \
                                border-top: 2px solid transparent; \
                                border-top-left-radius: 20px;\
                                border-top-right-radius: 20px; \
                                border-bottom-left-radius: 20px; \
                                border-bottom-right-radius: 20px; \
                                border-radius: 20px;  \
                                background-color: transparent; \
                                background-position: left center;\
                                background-repeat: no-repeat;\
                                }\
                                QPushButton:hover{\
                                    color: white;\
                                }\
                                QPushButton:pressed{\
                                    color: #BDC8E2;\
                                }"








#define TEXTEDIT_STYLE                 "QScrollBar:vertical {width:8px; background:rgba(0,0,0,0%);}"\
                                        "QScrollBar::handle:vertical {width:8px; background:rgba(78, 76, 69,50%); border-radius:4px;}"\
                                        "QScrollBar::add-line:vertical {width:0px; height:0px;}"\
                                        "QScrollBar::sub-line:vertical {width:0px; height:0px;}"\
                                        "QScrollBar::handle:vertical:hover {width:8px; background:rgba(78, 76, 69,100%); border-radius:4px;}"\
                                        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical {background:rgba(0,0,0,0%);}"





#define TABWIGHT_STYLE                  "QWidget\
                                        {\
                                        font: 14pt \"Ubuntu\";\
                                        }\
                                        QWidget#pageZero\
                                        {\
                                            background-color:rgb(180,180,239);\
                                        }\
                                        QTabBar::tab\
                                        {\
                                        min-width:80;\
                                        max-width:160;\
                                        height:35;\
                                        }\
                                        QTabBar::tab:focus\
                                        {\
                                        outline:none;\
                                        }\
                                        QTabWidget:pane\
                                        { \
                                        background-color:rgb(179,178,255); \
                                        border: -1px solid ; \
                                        top:0px solid;\
                                        } \
                                        QTabBar::tab:selected\
                                        {\
                                        margin-right: 5px rgb(235,237,239);\
                                        border-bottom: 5px solid rgb(255,255,255);\
                                        background-color:rgb(150,150,255);\
                                        }\
                                        QTabBar::tab:!selected\
                                        {\
                                        margin-right: 5px rgb(235,237,239); \
                                        border-bottom: 5px solid rgb(235,237,239);\
                                        background-color:rgb(200,200,200);\
                                        }\
                                        QTabBar::scroller {\
                                        border: -1px solid ; \
                                        width:30;\
                                        }"

#define TABLE_WIDGET_STYLE              "QHeaderView\
                                        {\
                                            background:transparent;\
                                        }\
                                        QHeaderView::section\
                                        {\
                                            font-size:14px;\
                                            font-family:\"Microsoft YaHei\";\
                                            color:#FFFFFF;\
                                            background:#60669B;\
                                            border:none; \
                                            text-align:left; \
                                            min-height:49px;   \
                                            max-height:49px;  \
                                            margin-left:0px; \
                                            padding-left:0px; \
                                        }\
                                        QTableWidget\
                                        {\
                                            background:#FFFFFF;\
                                            border:none;  \
                                            font-size:13px; \
                                            font-family:\"Microsoft YaHei\";\
                                            color:#666666; \
                                        }\
                                        QTableWidget::item  \
                                        {\
                                            border-bottom:1px solid #EEF1F7 ; \
                                        }\
                                        QTableWidget::item::selected \
                                        {\
                                            color:red; \
                                            background:#EFF4FF; \
                                        }\
                                        QScrollBar::handle:vertical \
                                        {\
                                            background: rgba(255,255,255,20%);\
                                            border: 0px solid grey;          \
                                            border-radius:3px;           \
                                            width: 8px;         \
                                        }\
                                        QScrollBar::vertical            \
                                        {\
                                            border-width:1px;   \
                                            border-style: solid;  \
                                            border-color: rgba(255, 255, 255, 10%); \
                                            width: 8px;  \
                                            margin:0px 0px 0px 0px;\
                                            border-radius:3px;\
                                        }\
                                        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
                                        {\
                                            background:rgba(255,255,255,10%); \
                                        }\
                                        QScollBar::add-line:vertical, QScrollBar::sub-line:vertical  \
                                        {\
                                            background:transparent; \
                                        }"








#define TABLE_WIDGET_STYLE2              "QHeaderView\
                                        {\
                                            background:transparent;\
                                        }\
                                        QHeaderView::section\
                                        {\
                                            font-size:14px;\
                                            font-family:\"Microsoft YaHei\";\
                                            color:#FFFFFF;\
                                            background:#4e9b5f;\
                                            border:none; \
                                            text-align:left; \
                                            min-height:35px;   \
                                            max-height:35px;  \
                                            margin-left:0px; \
                                            padding-left:0px; \
                                        }\
                                        QTableWidget\
                                        {\
                                            background:#e4c0fa;\
                                            border:none;  \
                                            font-size:13px; \
                                            font-family:\"Microsoft YaHei\";\
                                            color:#666666; \
                                        }\
                                        QTableWidget::item  \
                                        {\
                                            border-bottom:1px solid #EEF1F7 ; \
                                        }\
                                        QTableWidget::item::selected \
                                        {\
                                            color:red; \
                                            background:#EFF4FF; \
                                        }\
                                        QScrollBar::handle:vertical \
                                        {\
                                            background: rgba(255,255,255,20%);\
                                            border: 0px solid grey;          \
                                            border-radius:3px;           \
                                            width: 8px;         \
                                        }\
                                        QScrollBar::vertical            \
                                        {\
                                            border-width:1px;   \
                                            border-style: solid;  \
                                            border-color: rgba(255, 255, 255, 10%); \
                                            width: 8px;  \
                                            margin:0px 0px 0px 0px;\
                                            border-radius:3px;\
                                        }\
                                        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
                                        {\
                                            background:rgba(255,255,255,10%); \
                                        }\
                                        QScollBar::add-line:vertical, QScrollBar::sub-line:vertical  \
                                        {\
                                            background:transparent; \
                                        }"




#define TABLE_WIDGET_STYLE3              "QHeaderView\
                                        {\
                                            background:transparent;\
                                        }\
                                        QHeaderView::section\
                                        {\
                                            font-size:14px;\
                                            font-family:\"Microsoft YaHei\";\
                                            color:#FFFFFF;\
                                            background:#66cf9e;\
                                            border:none; \
                                            text-align:left; \
                                            min-height:49px;   \
                                            max-height:49px;  \
                                            margin-left:0px; \
                                            padding-left:0px; \
                                        }\
                                        QTableWidget\
                                        {\
                                            background:#afc1e9;\
                                            border:none;  \
                                            font-size:13px; \
                                            font-family:\"Microsoft YaHei\";\
                                            color:#666666; \
                                        }\
                                        QTableWidget::item  \
                                        {\
                                            border-bottom:1px solid #EEF1F7 ; \
                                        }\
                                        QTableWidget::item::selected \
                                        {\
                                            color:red; \
                                            background:#EFF4FF; \
                                        }\
                                        QScrollBar::handle:vertical \
                                        {\
                                            background: rgba(255,255,255,20%);\
                                            border: 0px solid grey;          \
                                            border-radius:3px;           \
                                            width: 8px;         \
                                        }\
                                        QScrollBar::vertical            \
                                        {\
                                            border-width:1px;   \
                                            border-style: solid;  \
                                            border-color: rgba(255, 255, 255, 10%); \
                                            width: 8px;  \
                                            margin:0px 0px 0px 0px;\
                                            border-radius:3px;\
                                        }\
                                        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\
                                        {\
                                            background:rgba(255,255,255,10%); \
                                        }\
                                        QScollBar::add-line:vertical, QScrollBar::sub-line:vertical  \
                                        {\
                                            background:transparent; \
                                        }"



#endif // CONFIG_H
