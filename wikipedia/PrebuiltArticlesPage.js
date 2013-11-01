const GObject = imports.gi.GObject;
const Gtk = imports.gi.Gtk;
const Lang = imports.lang;

const EndlessWikipedia = imports.wikipedia.EndlessWikipedia;

GObject.ParamFlags.READWRITE = GObject.ParamFlags.READABLE | GObject.ParamFlags.WRITABLE;

const PrebuiltArticlesPage = new Lang.Class({
    Name: 'PrebuiltArticlesPage',
    Extends: Gtk.Frame,
    Properties: {
        'article-title': GObject.ParamSpec.string('article-title',
            'Article title',
            'Human-readable title for the article to be displayed',
            GObject.ParamFlags.READWRITE | GObject.ParamFlags.CONSTRUCT,
            ''),
        'article-source': GObject.ParamSpec.string('article-source',
            'Article source',
            'Source website or database that the article comes from',
            GObject.ParamFlags.READWRITE | GObject.ParamFlags.CONSTRUCT,
            'Wikipedia'),
        'article-uri': GObject.ParamSpec.string('article-uri',
            'Article URI',
            'Wikipedia URI for the article to be displayed',
            GObject.ParamFlags.READWRITE | GObject.ParamFlags.CONSTRUCT,
            '')
    },

    _init: function(props) {
        this._article_title = null;
        this._article_uri = null;
        this._article_source = null;

        // Empty array is placeholder until we get baby page rank
        this._wiki_view = new EndlessWikipedia.WikipediaWebView({
            expand: true,
            hide_links: true
        });

        this.parent(props);

        this.add(this._wiki_view);

        // Add style contexts for CSS
        let context = this.get_style_context();
        context.add_class(EndlessWikipedia.STYLE_CLASS_ARTICLES_PAGE);
    },

    setShowableLinks: function(linked_articles) {
        this._wiki_view.setShowableLinks(linked_articles);
    },

    set_app_name: function (app_name) {
        this._wiki_view.app_name = app_name;
    },

    set_personality: function (personality) {
        this._wiki_view.system_personality = personality;
    },

    get article_title() {
        return this._article_title;
    },

    set article_title(value) {
        this._article_title = value;
    },

    get article_uri() {
        return this._article_uri;
    },

    set article_uri(value) {
        this._article_uri = value;
        if(value !== null && value !== "") {
            let url_parts = this._article_uri.split("/");
            let suffix = decodeURI(url_parts[url_parts.length-1]);
            this._wiki_view.loadArticleById(suffix, this.article_source);
        }
    }
});