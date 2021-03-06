'use strict';

function postFancybox(args, content) {
  args = args.join(' ').split(',');
  var cls = args[0];
  var col = Number(args[1]) || 0;
  if (col > 0) {
    return `<div class="fancybox ${cls}" col='${col}'>
              ${hexo.render.renderSync({text: content, engine: 'markdown'}).split('\n').join('')}
            </div>`;
  } else {
    return `<div class="fancybox ${cls}">
              ${hexo.render.renderSync({text: content, engine: 'markdown'}).split('\n').join('')}
            </div>`;
  }
}

hexo.extend.tag.register('fancybox', postFancybox, {ends: true});
