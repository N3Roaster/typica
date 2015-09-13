e.forEach(function(item) {
    var element = document.createElement("a");
    element.href="typica://script/" + item.dbid
    var colordiv;
    if(item.completion >= 1)
    {
        colordiv = '<div class="red"></div>';
    }
    else
    {
        colordiv = '<div class="orange"></div>';
    }
    if(item.completion < 0.6)
    {
        colordiv = '<div class="yellow"></div>';
    }
    if(item.completion < 0.3)
    {
        colordiv = '<div class="green"></div>';
    }
    element.innerHTML = '<div class="reminder">' + colordiv + '<span class="title">' + item.title + '</span><span class="progress">' + Math.floor(item.completion * 100) + '%</span><span class="detail">' + item.detail + '</span><div class="clearfix"></div></div>';
    document.body.appendChild(element);
})