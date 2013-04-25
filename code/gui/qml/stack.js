var stack = []

function push(element)
{
    if(stack.length > 0)
    {
        stack[stack.length-1].parent = null
    }

    stack.push(element)
}

function pop()
{
    var element = stack.pop()
    return element
}



function top()
{
    return stack[stack.length-1]
}

function get(i)
{
    return stack[i]
}

function count()
{
    return stack.length
}


function removeAt(i)
{
    var element = stack[i]
    stack.splice(i, 1);
}
