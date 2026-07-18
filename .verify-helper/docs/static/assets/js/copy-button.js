window.addEventListener('load', function(){
    const unbundle = function () {
        $('#unbundled').each(function(index, element) {
            $(element).parent().next().show();
        });
        $('#bundled').each(function(index, element) {
            $(element).parent().next().hide();
        });
        $('.code-bundle-btn').each(function(index, element) {
            $(element).text("Bundle");
        });
    };
    const bundle = function () {
        $('#unbundled').each(function(index, element) {
            $(element).parent().next().hide();
        });
        $('#bundled').each(function(index, element) {
            $(element).parent().next().show();
        });
        $('.code-bundle-btn').each(function(index, element) {
            $(element).text("Unbundle");
        });
    };

    // bundle 結果に verification-helper が追加する #line は表示・コピーから除く
    $('#bundled').each(function(index, element) {
        const code = $(element).parent().next().find('pre > code');
        code.find('span.cp').each(function(index, span) {
            if (/^#line\s+\d+\s+"(?:[^"\\]|\\.)*"\s*$/.test($(span).text())) {
                $(span).remove();
            }
        });
    });

    // ボタンを実装
    $('pre > code').each(function(index, element) {
        $(element).parent().wrap('<div style="position: relative;"></div>');
        $(element).parent().parent().append('<button type="button" class="code-btn code-copy-btn" title="Copied!">Copy</button>');
        $(element).parent().parent().append('<button type="button" class="code-btn code-bundle-btn" title="Bundled!">Bundle</button>');
    });

    // bundle されたコードを最初から表示する
    let is_bundled = true;
    bundle();

    $('.code-copy-btn').on('click',function(){
        // テキスト要素を選択＆クリップボードにコピー
        var textElem = $(this).siblings(':first');
        window.getSelection().selectAllChildren(textElem[0]);
        document.execCommand("copy");
        window.getSelection().removeAllRanges();

        // コピー完了を通知
        $(this).showBalloon();
        const this_ = this;
        setTimeout(function() {
            $(this_).hideBalloon();
        }, 300);
    });

    $('.code-bundle-btn').on('click', function(){
        // bundle / unbundle の切り替え
        if (is_bundled) {
            unbundle();
        } else {
            bundle();
        }
        is_bundled = ! is_bundled;
    });
});
